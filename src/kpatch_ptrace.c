#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <asm/unistd.h>

#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <linux/auxvec.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "kpatch_process.h"
#include "kpatch_common.h"
#include "kpatch_ptrace.h"
#include "kpatch_log.h"

#include <gelf.h>

/* process's memory access */
int
kpatch_process_mem_read(kpatch_process_t *proc,
			unsigned long src,
			void *dst,
			size_t size)
{
	int ret = pread(proc->memfd, dst, size, (off_t)src);
    if(ret <= 0) {
        err_log("pread failed, %s\n", strerror(errno));
    }
    return ret;
}

static int
kpatch_process_mem_write_ptrace(kpatch_process_t *proc,
				void *src,
				unsigned long dst,
				size_t size)
{
	int ret;

	while (ROUND_DOWN(size, sizeof(long)) != 0) {
		ret = ptrace(PTRACE_POKEDATA, proc->pid, dst,
			     *(unsigned long *)src);
		if (ret)
			return -1;

		dst += sizeof(long);
		src += sizeof(long);
		size -= sizeof(long);
	}

	if (size) {
		unsigned long tmp;

		tmp = ptrace(PTRACE_PEEKDATA, proc->pid, dst, NULL);
		if (tmp == (unsigned long)-1 && errno)
			return -1;
		memcpy(&tmp, src, size);

		ret = ptrace(PTRACE_POKEDATA, proc->pid, dst, tmp);
		if (ret)
			return -1;
	}

	return 0;
}

int
kpatch_process_mem_write(kpatch_process_t *proc,
			 void *src,
			 unsigned long dst,
			 size_t size)
{
	static int use_pwrite = 1;
	ssize_t w;

	if (use_pwrite)
		w = pwrite(proc->memfd, src, size, (off_t)dst);
	if (!use_pwrite || (w == -1 && errno == EINVAL)) {
		use_pwrite = 0;
		return kpatch_process_mem_write_ptrace(proc, src, dst, size);
	}

	return w != size ? -1 : 0;
}

struct process_mem_iter *
kpatch_process_mem_iter_init(kpatch_process_t *proc)
{
	struct process_mem_iter *iter;
	size_t pagesize = sysconf(_SC_PAGESIZE);

	iter = malloc(sizeof(*iter) + pagesize);
	if (!iter)
		return NULL;

	iter->proc = proc;
	iter->buflen = 0;

	iter->buffer_size = pagesize;

	return iter;
}

void kpatch_process_mem_iter_free(struct process_mem_iter *iter)
{
	free(iter);
}

int kpatch_process_mem_iter_peek(struct process_mem_iter *iter,
				 void *dst, size_t size,
				 unsigned long remote_addr)
{
	if (size > iter->buffer_size) {
		return kpatch_process_mem_read(iter->proc, remote_addr, dst, size);
	}

	if (iter->buflen == 0 ||
	    remote_addr < iter->base ||
	    remote_addr + size > iter->base + iter->buflen) {
		int ret;

		iter->base = remote_addr;
		ret = kpatch_process_mem_read(iter->proc,
					      remote_addr,
					      iter->buffer,
					      iter->buffer_size);
		if (ret < size)
			return -1;
		iter->buflen = ret;
	}

	memcpy(dst, iter->buffer + (remote_addr - iter->base), size);
	return 0;
}

int kpatch_process_mem_iter_peek_ulong(struct process_mem_iter *iter,
				       unsigned long *dst,
				       unsigned long remote_addr)
{
	return kpatch_process_mem_iter_peek(iter, dst, sizeof(*dst), remote_addr);
}

/* FIXME(pboldin): read these from /proc/pid/auxv */
int kpatch_ptrace_get_entry_point(struct kpatch_ptrace_ctx *pctx,
				  unsigned long *pentry_point)
{
	int ret;
	unsigned long *rstack, val;
	struct user_regs_struct regs;
	struct process_mem_iter *iter;

	kpdebug("Looking for entry point...");

	ret = ptrace(PTRACE_GETREGS, pctx->pid, NULL, &regs);
	if (ret < 0) {
		kplogerror("can't get regs\n");
		return -1;
	}

	iter = kpatch_process_mem_iter_init(pctx->proc);
	if (!iter) {
		kplogerror("can't allocate iterator\n");
		return -1;
	}

	/* Read stack and look for AUX data */
	rstack = (unsigned long*)regs.rsp;

	/* rstack now points to envs */
	rstack += PEEK_ULONG(rstack) + 2;

	/* Skip envs */
	for (; PEEK_ULONG(rstack); rstack++)
		continue;

	/* Now got to AUX */
	for (rstack++; (val = PEEK_ULONG(rstack)) != AT_NULL; rstack += 2) {
		if (val == AT_ENTRY) {
			*pentry_point = PEEK_ULONG(rstack + 1);
			break;
		}
	}

	if (val != AT_ENTRY)
		kpdebug("FAIL\n");
	else
		kpdebug("OK\n");

	kpatch_process_mem_iter_free(iter);

	return val == AT_ENTRY ? 0 : -1;
}

#define BREAK_INSN_LENGTH	1
#define BREAK_INSN		{0xcc}

#define SEC_TO_MSEC	1000
#define MSEC_TO_NSEC	1000000

#define for_each_thread(proc, pctx)	\
	list_for_each_entry(pctx, &proc->ptrace.pctxs, list)

static struct kpatch_ptrace_ctx *
kpatch_ptrace_find_thread(kpatch_process_t *proc,
			  pid_t pid,
			  unsigned long rip)
{
	struct kpatch_ptrace_ctx *pctx;

	for_each_thread(proc, pctx) {
		/* Check that we stopped the right thread */
		if (pctx->pid == pid) {
			if (rip == 0UL)
				return pctx;

			if (pctx->execute_until != 0UL &&
			    rip == pctx->execute_until + BREAK_INSN_LENGTH)
				return pctx;

			break;
		}
	}

	return NULL;
}

static inline int
kpatch_ptrace_waitpid(kpatch_process_t *proc,
		      struct timespec *timeout,
		      const sigset_t *sigset)
{
	struct kpatch_ptrace_ctx *pctx;
	siginfo_t siginfo;
	int ret, status;
	pid_t pid;
	struct user_regs_struct regs;

	/* Immediately reap one attached thread */
	pid = waitpid(-1, &status, __WALL | WNOHANG);

	if (pid < 0) {
		kplogerror("can't wait for tracees\n");
		return -1;
	}

	/* There is none ready, wait for notification via signal */
	if (pid == 0) {
		ret = sigtimedwait(sigset, &siginfo, timeout);
		if (ret == -1 && errno == EAGAIN) {
			/* We have timeouted */
			return -1;
		}

		if (ret == -1 && errno == EINVAL) {
			kperr("invalid timeout\n");
			return -1;
		}

		/* We have got EINTR and must restart */
		if (ret == -1 && errno == EINTR)
			return 0;

		/**
		 * Kernel stacks signals that follow too quickly.
		 * Deal with it by waiting for any child, not just
		 * one that is specified in signal
		 */
		pid = waitpid(-1, &status, __WALL | WNOHANG);

		if (pid == 0) {
			kperr("missing waitpid for %d\n", siginfo.si_pid);
			return 0;
		}

		if (pid < 0) {
			kplogerror("can't wait for tracee %d\n", siginfo.si_pid);
			return -1;
		}
	}

	if (!WIFSTOPPED(status) && WIFSIGNALED(status)) {
		/* Continue, resending the signal */
		ret = ptrace(PTRACE_CONT, pid, NULL,
			     (void *)(uintptr_t)WTERMSIG(status));
		if (ret < 0) {
			kplogerror("can't start tracee %d\n", pid);
			return -1;
		}
		return 0;
	}

	if (WIFEXITED(status)) {
		pctx = kpatch_ptrace_find_thread(proc, pid, 0UL);
		if (pctx == NULL) {
			kperr("got unexpected child '%d' exit\n", pid);
		} else {
			/* It's dead */
			pctx->pid = pctx->running = 0;
		}
		return 1;
	}

	ret = ptrace(PTRACE_GETREGS, pid, NULL, &regs);
	if (ret < 0) {
		kplogerror("can't get regs %d\n", pid);
		return -1;
	}

	pctx = kpatch_ptrace_find_thread(proc, pid, regs.rip);

	if (pctx == NULL) {
		/* We either don't know anything about this thread or
		 * even worse -- we stopped it in the wrong place.
		 * Bail out.
		 */
		pctx = kpatch_ptrace_find_thread(proc, pid, 0);
		if (pctx != NULL)
			pctx->running = 0;

		/* TODO: fix the latter by SINGLESTEPping such a thread with
		 * the original instruction in place */
		kperr("the thread ran out: %d, rip = %llx, expected = %lx\n", pid,
		      regs.rip, pctx->execute_until);
		errno = ESRCH;
		return -1;
	}

	pctx->running = 0;

	/* Restore thread registers, pctx is now valid */
	kpdebug("Got thread %d at %llx\n", pctx->pid,
		regs.rip - BREAK_INSN_LENGTH);

	regs.rip = pctx->execute_until;

	ret = ptrace(PTRACE_SETREGS, pctx->pid, NULL, &regs);
	if (ret < 0) {
		kplogerror("can't set regs - %d\n", pctx->pid);
		return -1;
	}

	return 1;
}

struct breakpoint {
	unsigned long addr;
	unsigned char orig_code[BREAK_INSN_LENGTH];
};

/* NOTE(pboldin) this code is pretty confusing and surely is platform-specific
 * in sense of the kernel version. This should be more extensively tested */
int
kpatch_ptrace_execute_until(kpatch_process_t *proc,
			    int timeout_msec,
			    int flags)
{
	int ret = 0, errno_save;
	char break_code[] = BREAK_INSN;
	struct breakpoint *bkpts;
	size_t has_target, running, to_be_stopped, bkpt_installed, i;
	sigset_t sigset, oldsigset;
	struct timespec timeout, start, current;

	struct kpatch_ptrace_ctx *pctx;

	has_target = 0;
	for_each_thread(proc, pctx)
		if (pctx->execute_until != 0UL)
			has_target++;

	if (has_target == 0)
		return 0;

	bkpts = calloc(has_target, sizeof(*bkpts));
	if (bkpts == NULL)
		return -1;

	bkpt_installed = 0;
	for_each_thread(proc, pctx) {

		if (pctx->execute_until == 0UL)
			continue;

		for (i = 0; i < bkpt_installed; i++) {
			if (bkpts[i].addr == pctx->execute_until)
				break;
		}

		if (i != bkpt_installed) {
			kpdebug("breakpoint at %lx already installed\n",
				pctx->execute_until);
			continue;
		}

		bkpts[bkpt_installed].addr = pctx->execute_until;

		kpdebug("Installing break at %lx...\n",
			bkpts[bkpt_installed].addr);

		ret = kpatch_process_mem_read(proc,
				bkpts[bkpt_installed].addr,
				(void *)bkpts[bkpt_installed].orig_code,
				BREAK_INSN_LENGTH);
		if (ret < 0) {
			kplogerror("cannot read orig code - %d\n", pctx->pid);
			goto poke_back;
		}

		ret = kpatch_process_mem_write(proc,
				break_code,
				bkpts[bkpt_installed].addr,
				BREAK_INSN_LENGTH);
		if (ret < 0) {
			kplogerror("cannot write break code - %d\n", pctx->pid);
			goto poke_back;
		}

		bkpt_installed++;
	}

	/* Block the SIGCHLD so we can use sigtimedwait */
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &sigset, &oldsigset) < 0)
		goto poke_back;

	running = 0;
	for_each_thread(proc, pctx) {
		kpdebug("Continuing thread %d until %lx...\n", pctx->pid, pctx->execute_until);

		if (!(flags & EXECUTE_ALL_THREADS) && pctx->execute_until == 0UL)
			continue;

		ret = ptrace(PTRACE_CONT, pctx->pid, NULL, NULL);
		if (ret < 0) {
			kplogerror("can't start tracee - %d\n", pctx->pid);
			goto restore_signals;
		}
		pctx->running = 1;
		running++;
	}

	to_be_stopped = has_target;
	while (running != 0 && to_be_stopped != 0 && timeout_msec >= 0) {
		int rv, dt;

		timeout.tv_sec = timeout_msec / SEC_TO_MSEC;
		timeout.tv_nsec = (timeout_msec % SEC_TO_MSEC) * MSEC_TO_NSEC;

		if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) {
			kplogerror("can't get start time\n");
			break;
		}

		rv = kpatch_ptrace_waitpid(proc, &timeout, &sigset);
		if (rv < 0)
			break;

		if (clock_gettime(CLOCK_MONOTONIC, &current) < 0) {
			kplogerror("can't get current time\n");
			break;
		}

		if (rv == 1) {
			to_be_stopped--;
			running--;
		}

		dt = (current.tv_sec - start.tv_sec) * SEC_TO_MSEC +
		     (current.tv_nsec - start.tv_nsec) / MSEC_TO_NSEC;

		timeout_msec -= dt;

		kpdebug("Passed %d msecs\n", dt);
	}

	kpdebug("left %d msecs\n", timeout_msec);

restore_signals:
	errno_save = errno;
	if (sigprocmask(SIG_SETMASK, &oldsigset, NULL) < 0) {
		kplogerror("unable to restore original signals\n");
	}
	errno = errno_save;

poke_back:
	errno_save = errno;

	i = 0;
	for_each_thread(proc, pctx) {
		int status;

		if (!pctx->running)
			continue;

		if (syscall(SYS_tgkill, proc->pid, pctx->pid, SIGSTOP) < 0)
			kplogerror("can't tkill %d\n", pctx->pid);

		while (errno != ESRCH && errno != ECHILD) {
			ret = waitpid(pctx->pid, &status, __WALL);
			if (ret < 0)
				kplogerror("can't wait for %d\n",
					   pctx->pid);

			if (WIFSTOPPED(status) || WIFEXITED(status) ||
			    errno == ECHILD)
				break;

			status = WTERMSIG(status);
			ret = ptrace(PTRACE_CONT, pctx->pid, NULL,
				     (void *)(uintptr_t)status);
			if (ret < 0)
				kplogerror("Can't continue thread %d\n",
					   pctx->pid);
		}

		pctx->running = 0;
	}

	for (i = 0; i < bkpt_installed; i++) {
		ret = kpatch_process_mem_write(
			proc,
			(void *)bkpts[i].orig_code,
			bkpts[i].addr,
			BREAK_INSN_LENGTH);

		if (ret < 0) {
			kplogerror("can't restore breakpoint - %lx\n",
				   bkpts[i].addr);
		}

		for_each_thread(proc, pctx)
			if (pctx->execute_until == bkpts[i].addr)
				pctx->execute_until = 0;
	}

	for_each_thread(proc, pctx) {
		if (pctx->execute_until != 0UL)
			kpwarn("thread %d still wants to break at 0x%lx\n",
			       pctx->pid, pctx->execute_until);
	}

	free(bkpts);

	if (i != bkpt_installed)
		kpwarn("Missing some original code, huh?\n");

	errno = errno_save;

	return ret;
}

static void copy_regs(struct user_regs_struct *dst,
		      struct user_regs_struct *src)
{
#define COPY_REG(x) dst->x = src->x
	COPY_REG(r15);
	COPY_REG(r14);
	COPY_REG(r13);
	COPY_REG(r12);
	COPY_REG(rbp);
	COPY_REG(rbx);
	COPY_REG(r11);
	COPY_REG(r10);
	COPY_REG(r9);
	COPY_REG(r8);
	COPY_REG(rax);
	COPY_REG(rcx);
	COPY_REG(rdx);
	COPY_REG(rsi);
	COPY_REG(rdi);
#undef COPY_REG
}

/**
 *  在 进程 中执行一个代码
 *
 *  1. 保存进程当前寄存器状态
 *  2. 读取当前进程 代码段中的代码，并保存到临时变量中(这里默认使用了 libc 的起始地址)
 *  3. 在
 */
static int
kpatch_execute_remote_func(struct kpatch_ptrace_ctx *pctx,
			   const unsigned char *code,
			   size_t codelen,
			   struct user_regs_struct *pregs,
			   int (*func)(struct kpatch_ptrace_ctx *pctx, void *data),
			   void *data)
{
	struct user_regs_struct orig_regs, regs;
	unsigned char orig_code[codelen];
	int ret;
	kpatch_process_t *proc = pctx->proc;

    /**
     *  libc 地址 - 这是 /proc/PID/maps 中 libc 地址最小的虚拟地址
     *
     *  荣涛 2021年9月18日
     *  
     *  这里如果随意定义一个 地址空间好像不行，比如也是属于 libc 的一个地址 0x7fae83c52000 ，为什么?
     *  答： 我认为需要有读写权限才行，比如说 pread 执行后errno为 Input/output error
     *      比如说，我查看 /proc/PID/maps 中看到 地址 7fdc4e879000 也属于 libc ，同时他的权限是 r--p, 
     *      这时候我们再进行测试，发现没有问题，如下所示
     *      cat /proc/PID/maps
     *      [...]
     *      7efc173aa000-7efc17566000 r-xp 00000000 fd:00 67110125 /usr/lib64/libc-2.28.so
     *      7efc17566000-7efc17765000 ---p 001bc000 fd:00 67110125 /usr/lib64/libc-2.28.so
     *      7efc17765000-7efc17769000 r--p 001bb000 fd:00 67110125 /usr/lib64/libc-2.28.so
     *      7efc17769000-7efc1776b000 rw-p 001bf000 fd:00 67110125 /usr/lib64/libc-2.28.so  
     */
	unsigned long libc_base = proc->libc_base; 
    debug_log("libc_base = %016lx.\n", libc_base);

    /**
     *  获取进程当前寄存器的副本
     */
	ret = ptrace(PTRACE_GETREGS, pctx->pid, NULL, &orig_regs);
	if (ret < 0) {
		kplogerror("can't get regs - %d\n", pctx->pid);
		return -1;
	}
    
    /**
     *  把原有的 代码拷贝到 临时变量中
     *  将 libc 其实代码位置覆盖，写入 我们的系统调用 - 这个系统调用对内存进行了mmap
     *  1. 首先，需要先保存原来的代码
     */
	ret = kpatch_process_mem_read(
        			      proc,
        			      libc_base,
        			      (unsigned long *)orig_code,
        			      codelen);
	if (ret < 0) {
		kplogerror("can't peek original code - %d\n", pctx->pid);
		return -1;
	}
    /**
     *  写入新的代码
     *  将 libc 其实代码位置覆盖，写入 我们的系统调用 - 这个系统调用对内存进行了mmap
     *  2. 然后，写入我们要写入的代码
     *  
     */
	ret = kpatch_process_mem_write(
        			      proc,
        			      (unsigned long *)code,
        			      libc_base,
        			      codelen);
	if (ret < 0) {
		kplogerror("can't poke syscall code - %d\n", pctx->pid);
		goto poke_back;
	}

    /**
     *  regs 赋值
     */
	regs = orig_regs;

    /**
     *  指令寄存器 指向 libc 基址
     *  因为我们上面，把自定义的指令拷贝到了 这个 libc_base 位置
     */
	regs.rip = libc_base;

    /**
     *  pregs 存放了 寄存器参数 - 这些参数用于传参
     *  比如，我们将 代码段的代码改为 自定义的指令后，需要寄存器进行传参，
     *  这里的 pregs 即为 参数。例如：
     *  
     *  code 为 syscall 指令
     *  pregs 即为 系统调用号，函数入参等信息。 
     *
     *  - 这里抛出一个问题，当我们需要调用超出 6 个参数时，这种方法好像就不适用了. ---荣涛 2021年9月18日
     */
	copy_regs(&regs, pregs);

    /**
     *  设置 寄存器 为 设置好的寄存器，即：
     *  rip = 自定义的指令，这里可以是 syscall 指令
     *  rax = 参数，如果 rip 对应系统调用，那么 rax = 系统调用号
     *  其他寄存器可以作为 函数调用的入参。
     */
	ret = ptrace(PTRACE_SETREGS, pctx->pid, NULL, &regs);
	if (ret < 0) {
		kplogerror("can't set regs - %d\n", pctx->pid);
		goto poke_back;
	}

    /**
     *  等待 = wait_for_stop()
     *  让程序继续执行， 里面使用了 ptrace(PTRACE_CONT, )
     */
	ret = func(pctx, data);
	if (ret < 0) {
		kplogerror("failed call to func\n");
		goto poke_back;
	}
    /**
     *  获取寄存器信息 
     *  再次获取寄存器信息，
     */
	ret = ptrace(PTRACE_GETREGS, pctx->pid, NULL, &regs);
	if (ret < 0) {
		kplogerror("can't get updated regs - %d\n", pctx->pid);
		goto poke_back;
	}
    /**
     *  恢复寄存器信息，
     *  将之前的寄存器设置到进程上下文中，继续执行
     */
	ret = ptrace(PTRACE_SETREGS, pctx->pid, NULL, &orig_regs);
	if (ret < 0) {
		kplogerror("can't restore regs - %d\n", pctx->pid);
		goto poke_back;
	}

    /**
     *  保存 注入代码 执行后 的寄存器状态
     */
	*pregs = regs;

poke_back:
    /**
     *  把进程地址空间代码段的进程修改回来
     */
	kpatch_process_mem_write(
        			proc,
        			(unsigned long *)orig_code,
        			libc_base,
        			codelen);
	return ret;
}

/**
 *  
 */
static int
wait_for_stop(struct kpatch_ptrace_ctx *pctx,
	      void *data)
{
	int ret, status = 0, pid = (int)(uintptr_t)data ?: pctx->pid;
	kpdebug("wait_for_stop(pctx->pid=%d, pid=%d)\n", pctx->pid, pid);

	while (1) {
        /**
         *  让程序继续执行
         */
		ret = ptrace(PTRACE_CONT, pctx->pid, NULL,
			     (void *)(uintptr_t)status);
		if (ret < 0) {
			kplogerror("can't start tracee %d\n", pctx->pid);
			return -1;
		}

		ret = waitpid(pid, &status, __WALL);
		if (ret < 0) {
			kplogerror("can't wait tracee %d\n", pid);
			return -1;
		}

        /**
         *  
         */
		if (WIFSTOPPED(status))  {
			if (WSTOPSIG(status) == SIGSTOP ||
			    WSTOPSIG(status) == SIGTRAP)
				break;
			status = WSTOPSIG(status);
			continue;
		}

		status = WIFSIGNALED(status) ? WTERMSIG(status) : 0;
	}

	return 0;
}

static int
wait_for_mmap(struct kpatch_ptrace_ctx *pctx,
	      unsigned long *pbase)
{
	int ret, status = 0, insyscall = 0;
	long rv;

	while (1) {
		ret = ptrace(PTRACE_SYSCALL, pctx->pid, NULL,
			     (void *)(uintptr_t)status);
		if (ret < 0) {
			kplogerror("can't PTRACE_SYSCALL tracee - %d\n",
				   pctx->pid);
			return -1;
		}

		ret = waitpid(pctx->pid, &status, __WALL);
		if (ret < 0) {
			kplogerror("can't wait tracee - %d\n", pctx->pid);
			return -1;
		}

		if (WIFEXITED(status)) {
			status = WTERMSIG(status);
			continue;
		} else if (!WIFSTOPPED(status)) {
			status = 0;
			continue;
		}

		status = 0;

		if (insyscall == 0) {
			rv = ptrace(PTRACE_PEEKUSER, pctx->pid,
				    offsetof(struct user_regs_struct,
					     orig_rax),
				    NULL);
			if (rv == -1) {
				kplogerror("ptrace(PTRACE_PEEKUSER)\n");
				return -1;
			}
			insyscall = rv;
			continue;
		} else if (insyscall == __NR_mmap) {
			rv = ptrace(PTRACE_PEEKUSER, pctx->pid,
				    offsetof(struct user_regs_struct,
					     rax),
				    NULL);
			*pbase = rv;
			break;
		}

		insyscall = !insyscall;
	}

	return 0;
}

/**
 *  注入代码
 */
int
kpatch_execute_remote(struct kpatch_ptrace_ctx *pctx,
		      const unsigned char *code,
		      size_t codelen,
		      struct user_regs_struct *pregs)
{
    /**
     *  
     */
	return kpatch_execute_remote_func(pctx,
                					  code,
                					  codelen,
                					  pregs,
                					  wait_for_stop,
                					  NULL);
}

/* FIXME(pboldin) buf might be too small */
static int
get_threadgroup_id(int tid)
{
	FILE *fh;
	char buf[256];
	int pid = -1;

	sprintf(buf, "/proc/%d/status", tid);

	fh = fopen(buf, "r");
	if (fh == NULL)
		return -1;

	while (!feof(fh)) {
		if (fscanf(fh, "Tgid: %d", &pid) == 1)
			break;
		fgets(buf, sizeof(buf), fh);
	}

	fclose(fh);
	return pid;
}

/**
 * This is rather tricky since we are accounting for the non-main
 * thread calling for execve(). See `ptrace(2)` for details.
 *
 * FIXME(pboldin): this is broken for multi-threaded calls
 * to execve. Sight.
 */
int
kpatch_ptrace_kickstart_execve_wrapper(kpatch_process_t *proc)
{
	int ret, pid = 0;
	struct kpatch_ptrace_ctx *pctx, *ptmp, *execve_pctx = NULL;
	long rv;

	kpdebug("kpatch_ptrace_kickstart_execve_wrapper\n");

	list_for_each_entry(pctx, &proc->ptrace.pctxs, list) {
		/* proc->pid equals to THREAD ID of the thread
		 * executing execve.so's version of execve
		 */
		if (pctx->pid != proc->pid)
			continue;
		execve_pctx = pctx;
		break;
	}

	if (execve_pctx == NULL) {
		kperr("can't find thread executing execve");
		return -1;
	}

	/* Send a message to our `execve` wrapper so it will continue
	 * execution
	 */
	ret = send(proc->send_fd, &ret, sizeof(ret), 0);
	if (ret < 0) {
		kplogerror("send failed\n");
		return ret;
	}

	/* Wait for it to reach BRKN instruction just before real execve */
	while (1) {
		ret = wait_for_stop(execve_pctx, NULL);
		if (ret < 0) {
			kplogerror("wait_for_stop\n");
			return ret;
		}

		rv = ptrace(PTRACE_PEEKUSER, execve_pctx->pid,
			    offsetof(struct user_regs_struct, rip),
			    NULL);
		if (rv == -1)
			return rv;

		rv = ptrace(PTRACE_PEEKTEXT, execve_pctx->pid,
			    rv - 1, NULL);
		if (rv == -1)
			return rv;
		if ((unsigned char)rv == 0xcc)
			break;
	}

	/* Wait for SIGTRAP from the execve. It happens from the thread
	 * group ID, so find it if thread doing execve() is not it. */
	if (execve_pctx != proc2pctx(proc)) {
		pid = get_threadgroup_id(proc->pid);
		if (pid < 0)
			return -1;

		proc->pid = pid;
	}

	ret = wait_for_stop(execve_pctx, (void *)(uintptr_t)pid);
	if (ret < 0) {
		kplogerror("waitpid\n");
		return ret;
	}

	list_for_each_entry_safe(pctx, ptmp, &proc->ptrace.pctxs, list) {
		if (pctx->pid == proc->pid)
			continue;
		kpatch_ptrace_detach(pctx);
		kpatch_ptrace_ctx_destroy(pctx);
	}

	/* Suddenly, /proc/pid/mem gets invalidated */
	{
		char buf[128];
		close(proc->memfd);

		snprintf(buf, sizeof(buf), "/proc/%d/mem", proc->pid);
		proc->memfd = open(buf, O_RDWR);
	}

	kpdebug("...done\n");

	return 0;
}

/**
 *  在另一个进程中 注入一个系统调用
 */
static int kpatch_syscall_remote(struct kpatch_ptrace_ctx *pctx, int nr,
		unsigned long arg1, unsigned long arg2, unsigned long arg3,
		unsigned long arg4, unsigned long arg5, unsigned long arg6,
		unsigned long *res)
{
	struct user_regs_struct regs;

	unsigned char syscall[] = {
		0x0f, 0x05, /* syscall */
		0xcc, /* int3 */
	};
	int ret;

    /**
     *  生成 mmap 系统调用
     *
     *  这里和我理解的 (以及测试的函数参数传递)有点不太一样，我测试的过程如下：
     *  
     *  rdi	传递第一个参数
     *  rsi	传递第二个参数
     *  rdx	传递第三个参数或者第二个返回值
     *  rcx	传递第四个参数 ### 不太一样
     *  r8	传递第五个参数
     *  r9	传递第六个参数
     *  rax	临时寄存器或者第一个返回值
     */
    //void *mmap(void *addr, size_t length, int prot, int flags,
    //                  int fd, off_t offset);
	kpdebug("Executing syscall %d (pid %d)...\n", nr, pctx->pid);
	regs.rax = (unsigned long)nr;
	regs.rdi = arg1;
	regs.rsi = arg2;
	regs.rdx = arg3;
	regs.r10 = arg4;
	regs.r8 = arg5;
	regs.r9 = arg6;

    /**
     *  注入代码，执行 mmap 映射
     */
	ret = kpatch_execute_remote(pctx, syscall, sizeof(syscall), &regs);
	if (ret == 0)
		*res = regs.rax;

	return ret;
}

int kpatch_ptrace_resolve_ifunc(struct kpatch_ptrace_ctx *pctx,
				unsigned long *addr)
{
	struct user_regs_struct regs;

	unsigned char callrax[] = {
		0xff, 0xd0, /* call *%rax */
		0xcc, /* int3 */
	};
	int ret;

	kpdebug("Executing callrax %lx (pid %d)\n", *addr, pctx->pid);
	regs.rax = *addr;

	ret = kpatch_execute_remote(pctx, callrax, sizeof(callrax), &regs);
	if (ret == 0)
		*addr = regs.rax;

	return ret;
}

#define MAX_ERRNO	4095

/**
 *  映射
 */
unsigned long
kpatch_mmap_remote(struct kpatch_ptrace_ctx *pctx,
		   unsigned long addr,
		   size_t length,
		   int prot,
		   int flags,
		   int fd,
		   off_t offset)
{
	int ret;
	unsigned long res;

	kpdebug("mmap_remote: 0x%lx+%lx, %x, %x, %d, %lx\n", addr, length,
		prot, flags, fd, offset);
    debug_log("mmap_remote: mmap(0x%lx, %ld, %x, %x, %d, %lx)\n", addr, length,
		prot, flags, fd, offset);
    
    /**
     *  比如说我们要执行一个 mmap
     *  
     *  void *mmap(void *addr, size_t length, int prot, int flags,
     *            int fd, off_t offset);
     */
	ret = kpatch_syscall_remote(pctx, __NR_mmap, (unsigned long)addr,
				                length, prot, flags, fd, offset, &res);
	if (ret < 0)
		return 0;
	if (ret == 0 && res >= (unsigned long)-MAX_ERRNO) {
		errno = -(long)res;
		return 0;
	}
	return res;
}

int kpatch_munmap_remote(struct kpatch_ptrace_ctx *pctx,
			 unsigned long addr,
			 size_t length)
{
	int ret;
	unsigned long res;

	kpdebug("munmap_remote: 0x%lx+%lx\n", addr, length);
	ret = kpatch_syscall_remote(pctx, __NR_munmap, (unsigned long)addr,
				    length, 0, 0, 0, 0, &res);
	if (ret < 0)
		return -1;
	if (ret == 0 && res >= (unsigned long)-MAX_ERRNO) {
		errno = -(long)res;
		return -1;
	}
	return 0;
}

int kpatch_arch_prctl_remote(struct kpatch_ptrace_ctx *pctx, int code, unsigned long *addr)
{
	struct user_regs_struct regs;
	unsigned long res, rsp;
	int ret;

	kpdebug("arch_prctl_remote: %d, %p\n", code, addr);
	ret = ptrace(PTRACE_GETREGS, pctx->pid, NULL, &regs);
	if (ret < 0) {
		kpdebug("FAIL. Can't get regs - %s\n", strerror(errno));
		return -1;
	}
	ret = kpatch_process_mem_read(pctx->proc,
				      regs.rsp,
				      &rsp,
				      sizeof(rsp));
	if (ret < 0) {
		kplogerror("can't peek original stack data\n");
		return -1;
	}
	ret = kpatch_syscall_remote(pctx, __NR_arch_prctl, code, regs.rsp, 0, 0, 0, 0, &res);
	if (ret < 0)
		goto poke;
	if (ret == 0 && res >= (unsigned long)-MAX_ERRNO) {
		errno = -(long)res;
		ret = -1;
		goto poke;
	}
	ret = kpatch_process_mem_read(pctx->proc,
				      regs.rsp,
				      &res,
				      sizeof(res));
	if (ret < 0)
		kplogerror("can't peek new stack data\n");

poke:
	if (kpatch_process_mem_write(pctx->proc,
				     &rsp,
				     regs.rsp,
				     sizeof(rsp)))
		kplogerror("can't poke orig stack data\n");
	*addr = res;
	return ret;
}

int
kpatch_remote_write(struct kpatch_ptrace_ctx *pctx,
		    unsigned long dst,
		    void *src,
		    size_t size)
{
	int ret;

	kpdebug("Copying 0x%lx bytes to target process's 0x%lx...", size, dst);
	ret = kpatch_process_mem_write(pctx->proc, src, dst, size);
	if (ret < 0)
		kpdebug("FAIL\n");
	else
		kpdebug("OK\n");
	return ret;
}

int
kpatch_process_memcpy(kpatch_process_t *proc,
		      unsigned long dst,
		      unsigned long src,
		      size_t size)
{
	int ret;
	char *buf;

	kpdebug("Copying 0x%lx bytes from 0x%lx to 0x%lx in target...",
		size, src, dst);

	buf = malloc(size);
	if (buf == NULL) {
		kpdebug("FAIL\n");
		return -1;
	}

	ret = kpatch_process_mem_read(proc, src, buf, size);
	if (ret > 0)
		ret = kpatch_process_mem_write(proc, buf, dst, size);

	if (ret < 0)
		kpdebug("FAIL\n");
	else
		kpdebug("OK\n");

	free(buf);

	return ret;
}

int
kpatch_ptrace_handle_ld_linux(kpatch_process_t *proc,
			      unsigned long *pentry_point)
{
	/* Wait until we have a first mmap */
	unsigned long orig;
	int ret;
	GElf_Ehdr ehdr;
	struct kpatch_ptrace_ctx *pctx = proc2pctx(proc);

	kpdebug("kpatch_ptrace_handle_ld_linux\n");

	ret = wait_for_mmap(pctx, &orig);
	if (ret == -1) {
		kperr("wait_for_mmap\n");
		return -1;
	}

	ret = kpatch_process_mem_read(proc, orig, &ehdr,
				      sizeof(GElf_Ehdr));
	if (ret == -1) {
		kplogerror("kpatch_ptrace_peek\n");
		return -1;
	}

	*pentry_point = ehdr.e_entry;
	if (ehdr.e_type == ET_DYN)
		*pentry_point += orig;

	kpinfo("ld_linux: orig = %lx, entry_point = %lx\n", orig, *pentry_point);

	return 0;
}

static struct kpatch_ptrace_ctx *
kpatch_ptrace_ctx_alloc(kpatch_process_t *proc)
{
	struct kpatch_ptrace_ctx *p;

	p = malloc(sizeof(*p));
	if (!p)
		return NULL;
	memset(p, 0, sizeof(*p));

	p->execute_until = 0UL;
	p->running = 1;
	p->proc = proc;

	list_init(&p->list);
	list_add(&p->list, &proc->ptrace.pctxs);
	return p;
}

void kpatch_ptrace_ctx_destroy(struct kpatch_ptrace_ctx *pctx)
{
	list_del(&pctx->list);
	free(pctx);
}

/**
 *  使用 ptrace 跟踪
 */
int kpatch_ptrace_attach_thread(kpatch_process_t *proc, int tid)
{
	long ret;
	int status;
	struct kpatch_ptrace_ctx *pctx;

    /**
     *  分配 内存，初始化链表 病添加到 全局链表里
     */
	pctx = kpatch_ptrace_ctx_alloc(proc);
	if (pctx == NULL) {
		kperr("Can't alloc kpatch_ptrace_ctx");
		return -1;
	}

    /**
     *  线程ID
     */
	pctx->pid = tid;
	kpdebug("Attaching to %d...", pctx->pid);
    debug_log("Attaching to %d...\n", pctx->pid);

    /**
     *  attach 进程
     */
	ret = ptrace(PTRACE_ATTACH, pctx->pid, NULL, NULL);
	if (ret < 0) {
		kplogerror("can't attach to %d\n", pctx->pid);
		return -1;
	}

	do {
        debug_log("waitpid(%d)\n", tid);
		ret = waitpid(tid, &status, __WALL);
		if (ret < 0) {
			kplogerror("can't wait for thread\n");
			return -1;
		}

		/* We are expecting SIGSTOP */
		if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGSTOP)
			break;

		/* If we got SIGTRAP because we just got out of execve, wait
		 * for the SIGSTOP
		 */
		if (WIFSTOPPED(status))
			status = (WSTOPSIG(status) == SIGTRAP) ? 0 : WSTOPSIG(status);
		else if (WIFSIGNALED(status))
			/* Resend signal */
			status = WTERMSIG(status);

        /**
         *  
         */
        debug_log("ptrace(PTRACE_CONT, %d)\n", tid);
		ret = ptrace(PTRACE_CONT, pctx->pid, NULL, (void *)(uintptr_t)status);
		if (ret < 0) {
			kplogerror("can't cont tracee\n");
			return -1;
		}
	} while (1);

	pctx->running = 0;

	kpdebug("OK\n");
	return 0;
}

int kpatch_ptrace_detach(struct kpatch_ptrace_ctx *pctx)
{
	long ret;

	if (!pctx->pid)
		return 0;
	kpdebug("Detaching from %d...", pctx->pid);
	ret = ptrace(PTRACE_DETACH, pctx->pid, NULL, NULL);
	if (ret < 0) {
		kplogerror("can't detach from %d\n", pctx->pid);
		return -1;
	}

	kpdebug("OK\n");

	pctx->running = 1;
	pctx->pid = 0;
	return 0;
}
