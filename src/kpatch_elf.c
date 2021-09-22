#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <limits.h>

#include <gelf.h>

#include "kpatch_common.h"
#include "kpatch_user.h"
#include "kpatch_process.h"
#include "kpatch_elf.h"
#include "kpatch_file.h"
#include "kpatch_ptrace.h"
#include "kpatch_log.h"

static int
elf_object_peek_phdr(struct object_file *o)
{
	int rv = 0;

	if (o->vma_start != ~(unsigned long)0)
		return 0;

    /**
     *  VMA 起始点
     */
	o->vma_start = list_first_entry(&o->vma, struct obj_vm_area, list)->inmem.start;

    /**
     *  ELF 文件头
     */
	if (o->ehdr.e_ident[0] != '\177') {
		rv = kpatch_process_mem_read(o->proc,
            					     o->vma_start,
            					     &o->ehdr,
            					     sizeof(o->ehdr));
		if (rv < 0)
			return rv;
	}

    /**
     *  程序头
     */
	if (o->phdr == NULL) {
        /**
         *  找到 ELF程序头位置
         */
		unsigned long phaddr = o->vma_start + o->ehdr.e_phoff;

        /**
         *  分配程序头
         */
		o->phdr = malloc(o->ehdr.e_phnum * sizeof(*o->phdr));
		if (o->phdr == NULL)
			return -1;

        /**
         *  拷贝这个程序头
         */
		rv = kpatch_process_mem_read(o->proc,
					     phaddr,
					     o->phdr,
					     sizeof(*o->phdr) * o->ehdr.e_phnum);
	}

	return rv;
}

/**
 *  给 ELF 文件设置程序头
 */
int
kpatch_elf_object_set_ehdr(struct object_file *o,
			   const unsigned char *buf,
			   size_t bufsize)
{
    debug_log("\n");
    /**
     *  大小 检测
     */
	if (bufsize < sizeof(o->ehdr))
		return 0;

    /**
     *  必须是 ELF 文件类型
     */
	if (memcmp(buf, ELFMAG, SELFMAG)) {
		kpdebug("magic(%s) = %x%x%x%x\n", o->name, buf[0], buf[1], buf[2], buf[3]);
		return -1;
	}

    /**
     *  拷贝这个 ELF 文件头
     */
	memcpy(&o->ehdr, buf, sizeof(o->ehdr));

    /**
     *  buffer 大小需要满足ELF 解析大小
     *  bufsize >= 程序头偏移 + 程序头大小*程序头数量
     *  
     */
	if (bufsize < o->ehdr.e_phoff + o->ehdr.e_phentsize * o->ehdr.e_phnum)
		return 0;

    /**
     *  分配程序头 ，当然这里采用 ELF64 作为目标文件
     */
	o->phdr = malloc(o->ehdr.e_phnum * sizeof(*o->phdr));
	if (o->phdr == NULL)
		return -1;

    /**
     *  直接拷贝这个程序头
     *  其实这里就有一点问题，当 输入的 ELF 于 目标 ELF64 不一致时候，该如何做。
     */
	memcpy(o->phdr, buf + o->ehdr.e_phoff,
	       o->ehdr.e_phentsize * o->ehdr.e_phnum);

	return 0;
}

static int
elf_object_look_for_buildid(struct object_file *o)
{
	int rv = -1;
	size_t i;
	char buf[128];

	rv = elf_object_peek_phdr(o);
	if (rv < 0)
		return rv;

	for (i = 0; i < o->ehdr.e_phnum; i++) {
		Elf64_Nhdr *nhdr = (void *)buf;
		char *data = buf + sizeof(*nhdr);
		size_t offset = o->phdr[i].p_offset;
		size_t lastoffset = offset + o->phdr[i].p_memsz;

		if (o->phdr[i].p_type != PT_NOTE)
			continue;
		if (o->phdr[i].p_memsz > sizeof(buf))
			continue;

		while (offset < lastoffset) {
			rv = kpatch_process_mem_read(o->proc,
						     o->vma_start + offset,
						     buf,
						     sizeof(buf));
			if (rv < 0)
				return rv;

			if (nhdr->n_namesz == 4 && !strcmp(data, "GNU") &&
			    nhdr->n_type == NT_GNU_BUILD_ID)
				break;

			offset += nhdr->n_namesz + nhdr->n_descsz + sizeof(*nhdr);
		}

		if (offset >= lastoffset)
			continue;

		data += nhdr->n_namesz;
		for (i = 0; i < 40; i+=2, data++)
			sprintf(o->buildid + i, "%02hhx", *data);

		kpdebug("read '%s'\n", o->buildid);

		return 0;
	}

	return -1;
}


const char *
kpatch_get_buildid(struct object_file *o)
{
	if (!o->is_elf)
		return NULL;

	if (o->buildid[0] == '\0') {
		int rv;

		kpdebug("Getting BuildID for '%s'...", o->name);
		rv = elf_object_look_for_buildid(o);

		if (rv < 0)
			return NULL;
	}

	return o->buildid;
}

static int
elf_object_is_interp_exception(struct object_file *o)
{
	/* libc */
	if (!strncmp(o->name, "libc", 4) &&
	    !strncmp(o->name + strlen(o->name) - 3, ".so", 3))
		return 1;
	/* libpthread */
	if (!strncmp(o->name, "libpthread", 10) &&
	    !strncmp(o->name + strlen(o->name) - 3, ".so", 3))
		return 1;
	/* libdl */
	if (!strncmp(o->name, "libdl", 5) &&
	    !strncmp(o->name + strlen(o->name) - 3, ".so", 3))
		return 1;
    /**
     *  MORE?
     */
     
	return 0;
}

/**
 *  ELF 是否为 动态库
 */
int kpatch_elf_object_is_shared_lib(struct object_file *o)
{
	size_t i;
	int rv;

	rv = elf_object_peek_phdr(o);
	if (rv < 0)
		return rv;

	/*
	 * If type of the ELF is not ET_DYN, this is definitely
	 * not a shared library
	 *  如果不是动态库，直接返回
	 *  ET_DYN 共享目标文件
	 */
	if (o->ehdr.e_type != ET_DYN) {
		return 0;
	}

	/*
	 * Now there are possibilities:
	 *   - either this is really a shared library
	 *   - or this is a position-independent executable
	 * To distinguish between them look for INTERP
	 * program header that mush be present in any valid
	 * executable or usually don't in shared libraries
	 * (notable exception - libc)
	 *
	 * 
	 */
	for (i = 0; i < o->ehdr.e_phnum/*程序头数量*/; i++) {
        /**
         *  PT_INTERP - 程序解释器位置的描述，如 /lib/ld-linux.so.2
         *  
         */
        /**
         *  如果是解释器 并且也不是 libc,libpthread,libdl 等
         */
		/* Ok, looks like this is an executable */
		if (o->phdr[i].p_type == PT_INTERP &&
		    !elf_object_is_interp_exception(o))
			return 0;
	}

    /**
     *  共享库文件
     */
	/* Ok, looks like this is a shared library */
	return 1;
}

static int prot2flags(unsigned int prot)
{
	unsigned int flags = 0;

	if (prot & PROT_READ)
		flags |= PF_R;
	if (prot & PROT_WRITE)
		flags |= PF_W;
	if (prot & PROT_EXEC)
		flags |= PF_X;
	return flags;
}

/**
 *  按照虚拟地址  和 segment 内存大小
 */
/* Sort by inclusion, so the previous PT_LOAD contains current PT_GNU_RELRO */
static int phdr_compare(const void *a, const void *b)
{
	const GElf_Phdr *pa = a, *pb = b;

	if (pa->p_vaddr < pb->p_vaddr)
		return -1;

	if (pa->p_vaddr > pb->p_vaddr)
		return 1;

	if (pa->p_memsz < pb->p_memsz)
		return 1;

	if (pa->p_memsz > pb->p_memsz)
		return -1;

	return 0;
}

#define PAGE_DOWN(x)	ROUND_DOWN(x, getpagesize())
#define PAGE_UP(x)	ROUND_UP(x, getpagesize())

/**
 *  
 */
static int match_program_header_vm_area(Elf64_Phdr *pphdr,
					struct obj_vm_area *ovma,
					unsigned long load_offset)
{
    /**
     *  start = 虚拟地址 + load_offset
     *  end = start + segment在文件中的大小
     */
	unsigned long start = pphdr->p_vaddr + load_offset;
	unsigned long end = start + pphdr->p_filesz;

	/* Whenever segment size in memory p_memsz > segment size in file
	 * (p_memsz > p_filesz) the rest of the segemnt memory is mapped by
	 * the glibc from the anonymous fd = -1, so we only match inmem.end
	 * against start + pphdr->p_filesz
	 *
     * TODO  
     */
	return (PAGE_DOWN(start) == ovma->inmem.start) &&
	       (PAGE_UP(end) == ovma->inmem.end) &&
	       ((pphdr->p_flags & (PF_R|PF_W|PF_X)) == prot2flags(ovma->inmem.prot));
}

/**
 *  解析 ELF 程序头
 */
int kpatch_elf_parse_program_header(struct object_file *o)
{
	Elf64_Phdr *maphdrs = NULL;

	unsigned long load_offset;
	unsigned long lowest_vaddr = ULONG_MAX;

	struct obj_vm_area *ovma;
	int rv = -1, errno_save;
	size_t i, j, nmaps;

    /**
     *  程序头
     */
	Elf64_Phdr *pphdr;

	kpdebug("Parsing program headers for '%s'...\n", o->name);

    /**
     *  拷贝 /proc/PID/maps 程序头到 数据结构 "o" 中
     */
	rv = elf_object_peek_phdr(o);
	if (rv < 0)
		return rv;

	/* First, find the load_offset that is the difference between lowest
	 * vma.inmem.start and lowest phdr.v_addr
	 */

    /**
     *  遍历所有程序头
     */
	/* Look for the lowest LOAD */
	for (i = 0, nmaps = 0; i < o->ehdr.e_phnum; i++) {
		pphdr = &o->phdr[i];
        /**
         *  程序头类型
         */
		switch (pphdr->p_type) {
        /**
         *  这是程序运行初期，从 ELF 文件被加载/映射 到 内存中的程序
         */
		case PT_LOAD:
            /**
             *  找到程序头中 的 最低地址
             */
			lowest_vaddr = lowest_vaddr > pphdr->p_vaddr
				       ? pphdr->p_vaddr : lowest_vaddr;
            /**
             *  程序在这里会继续执行
             */
			/* FALLTHROUGH */
        /**
         *  read only relocation.
         */
            debug_log("PT_GNU_RELRO before.\n");
		case PT_GNU_RELRO:
            debug_log("PT_GNU_RELRO after.\n");
			nmaps++;
			break;
		}
	}
    /**
     *  
     */
	if (lowest_vaddr == ULONG_MAX) {
		kperr("%s: unable to find lowest load address\n",
		      o->name);
		goto out;
	}

    /**
     *  向下对齐
     */
	lowest_vaddr = PAGE_DOWN(lowest_vaddr);

    /**
     *  
     */
	load_offset = o->vma_start - lowest_vaddr;
	o->load_offset = load_offset;

	kpinfo("%s: load offset: %lx = %lx - %lx\n",
	       o->name, load_offset, o->vma_start, lowest_vaddr);

    /**
     *  分配 即将映射的程序头
     */
	maphdrs = malloc(sizeof(*maphdrs) * nmaps);
	if (!maphdrs)
		goto out;

    /**
     *  给程序头赋值
     */
	for (i = 0, j = 0; i < o->ehdr.e_phnum; i++) {
		pphdr = &o->phdr[i];
		switch (pphdr->p_type) {
		case PT_LOAD:
		case PT_GNU_RELRO:
			maphdrs[j++] = *pphdr;
			break;
		}
	}
    /**
     *  排序
     */
	qsort(maphdrs, nmaps, sizeof(*maphdrs), phdr_compare);

    for (i = 0; i < nmaps; i++) {
		kpdebug("maphdrs[%ld] = { .p_vaddr = %lx, .p_memsz = %lx, .p_offset = %lx, .p_filesz = %lx }\n",
    			i,
    			maphdrs[i].p_vaddr, maphdrs[i].p_memsz,
    			maphdrs[i].p_offset, maphdrs[i].p_filesz);
        info_log("maphdrs[%ld] = { .p_vaddr = %lx, .p_memsz = %lx, .p_offset = %lx, .p_filesz = %lx }\n",
    			i,
    			maphdrs[i].p_vaddr, maphdrs[i].p_memsz,
    			maphdrs[i].p_offset, maphdrs[i].p_filesz);
	}

    /**
     *  
     */
	/* Account for GNU_RELRO */
	for (i = 0; i < nmaps; i++) {

        /**
         *  只处理 只读 relocation readonly
         */
		if (maphdrs[i].p_type != PT_GNU_RELRO)
			continue;

		if (i == 0) {
			kperr("%s: wrong ELF: PT_GNU_RELRO is first phdr\n",
			      o->name);
			goto out;
		}

        /**
         *  设置为 不可写
         */
		maphdrs[i].p_flags &= ~PF_W;

        /**
         *  如果上一个 程序 segment 虚拟地址相等
         */
		if (maphdrs[i - 1].p_vaddr == maphdrs[i].p_vaddr) {
            /**
             *  虚拟地址 
             */
			maphdrs[i - 1].p_vaddr = maphdrs[i].p_vaddr + maphdrs[i].p_memsz;
			maphdrs[i - 1].p_memsz -= maphdrs[i].p_memsz;

			maphdrs[i - 1].p_offset += maphdrs[i].p_filesz;
			maphdrs[i - 1].p_filesz -= maphdrs[i].p_filesz;
		} else {
			kperr("TODO: splitting VM by GNU_RELRO\n");
			goto out;
		}
	}

    /**
     *  
     */
	for (i = 0; i < nmaps; i++) {
		kpdebug("maphdrs[%ld] = { .p_vaddr = %lx, .p_memsz = %lx, .p_offset = %lx, .p_filesz = %lx }\n",
    			i,
    			maphdrs[i].p_vaddr, maphdrs[i].p_memsz,
    			maphdrs[i].p_offset, maphdrs[i].p_filesz);
        info_log("maphdrs[%ld] = { .p_vaddr = %lx, .p_memsz = %lx, .p_offset = %lx, .p_filesz = %lx }\n",
    			i,
    			maphdrs[i].p_vaddr, maphdrs[i].p_memsz,
    			maphdrs[i].p_offset, maphdrs[i].p_filesz);
	}

    /**
     *  遍历所有 VMA
     */
	list_for_each_entry(ovma, &o->vma, list) {
	    /**
         *  跳过 没有权限的
         */
		if (ovma->inmem.prot == PROT_NONE) {
			/* Ignore holes */
			continue;
		}

        /**
         *  遍历 segments
         */
		for (i = 0; i < nmaps; i++) {
			pphdr = &maphdrs[i];
            /**
             *  
             */
			if (match_program_header_vm_area(pphdr, ovma, load_offset))
				break;
		}
        /**
         *  没有找到
         */
		if (i == nmaps) {
			kperr("cant match ovma->inmem = { .start = %lx, .end = %lx, .prot = %x }\n",
			      ovma->inmem.start, ovma->inmem.end, ovma->inmem.prot);
			rv = -1;
			goto out;
		}

        /**
         *  
         */
		ovma->ondisk.start = pphdr->p_offset;
		ovma->ondisk.end = pphdr->p_offset + pphdr->p_filesz;
		ovma->ondisk.prot = ovma->inmem.prot;

		ovma->inelf.start = pphdr->p_vaddr;
		ovma->inelf.end = pphdr->p_vaddr + pphdr->p_memsz;
		ovma->inelf.prot = 0;

        /**
         *  
         */
		ovma->inmem.start = load_offset + ovma->inelf.start;
		ovma->inmem.end = load_offset + ovma->inelf.end;

        /**
         *  
         */
#define _kpdebug(fmt...) fprintf(stderr, fmt)
		_kpdebug(" phdr[%ld]{ .start = %lx, .end = %lx, prot = %x }",
        			i,
        			ovma->ondisk.start, ovma->ondisk.end,
        			ovma->ondisk.prot);
		_kpdebug(" <-> ");
		_kpdebug("{ .start = %lx, .end = %lx, prot = %x }\n",
			        ovma->inmem.start, ovma->inmem.end, ovma->inmem.prot);
#undef _kpdebug
	}

	rv = 0;
out:
	errno_save = errno;

	free(maphdrs);

	errno = errno_save;
	return rv;
}

/**
 *  
 */
static char *secname(GElf_Ehdr *ehdr, GElf_Shdr *s)
{
    /**
     *  ELF 文件头 + section header offset = section header
     */
	GElf_Shdr *shdr = (void *)ehdr + ehdr->e_shoff;
    /**
     *  e_shstrndx - Section header string table index
     *  
     */
	char *str = (void *)ehdr + shdr[ehdr->e_shstrndx].sh_offset;
    
	return str + s->sh_name;
}

/**
 *  
 */
static int kpatch_is_our_section(GElf_Shdr *s)
{
    /**
     *  原作者说这里需要 fix,
     *  我觉得这里需要添加更多的判断
     *  .bss 段 可能也是 SHT_NOBITS (8)
     *  
     *  这是在之前设置的 SHT_NOBITS， 利用 stripped 工具，这么一看，好像也够了
     */
	// FIXME: is this enough???
	return s->sh_type != SHT_NOBITS;
}

unsigned long vaddr2addr(struct object_file *o, unsigned long vaddr)
{
	struct obj_vm_area *ovma;

	if (vaddr == 0)
		return 0;
    /**
     *  
     */
	list_for_each_entry(ovma, &o->vma, list) {
		if (vaddr >= ovma->inelf.start && vaddr < ovma->inelf.end)
			return vaddr - ovma->inelf.start + ovma->inmem.start;
	}

	return 0;
}

/**
 *  分配 几个 jump table
 *
 *  Undefined symbol 'printf@@GLIBC_2.2.5'
 *  Undefined symbol 'puts@@GLIBC_2.2.5'
 */
struct kpatch_jmp_table *kpatch_new_jmp_table(int entries)
{
	struct kpatch_jmp_table *jtbl;
	size_t sz = sizeof(*jtbl) + entries * sizeof(struct kpatch_jmp_table_entry);

	jtbl = malloc(sz);
    assert(jtbl && "malloc jump  table failed.");
    
	memset(jtbl, 0, sz);
	jtbl->size = sz;
	jtbl->max_entry = entries;
	return jtbl;
}

static inline int
is_undef_symbol(const Elf64_Sym *sym)
{
	return sym->st_shndx == SHN_UNDEF || sym->st_shndx >= SHN_LORESERVE;
}

/**
 *  
 */
int kpatch_count_undefined(struct object_file *o)
{
	GElf_Ehdr *ehdr;
	GElf_Shdr *shdr;
	GElf_Sym *sym;
	int i, symidx = 0, count = 0;
	char *strsym;

	ehdr = (void *)o->kpfile.patch + o->kpfile.patch->kpatch_offset;
	shdr = (void *)ehdr + ehdr->e_shoff;

    /**
     *  遍历 section header 
     */
	for (i = 1; i < ehdr->e_shnum; i++) {
		GElf_Shdr *s = shdr + i;
        /**
         *  符号信息
         */
		if (s->sh_type == SHT_SYMTAB) {
			symidx = i;
			break;
		}
	}
    
	kpdebug("Counting undefined symbols:\n");
    /**
     *  符号信息便宜
     */
	sym = (void *)ehdr + shdr[symidx].sh_offset;
    /**
     *  sh_link - 链接到下一个 符号
     */
	strsym = (void *)ehdr + shdr[shdr[symidx].sh_link].sh_offset;

    /**
     *  节大小 / 符号项大小 = 个数
     */
	for (i = 1; i < shdr[symidx].sh_size / sizeof(GElf_Sym); i++) {
		GElf_Sym *s = sym + i;

        /**
         *  st_shndx 表明 符号表 和 某些节对应
         *          SHN_UNDEF - 未定义
         *
         *  st_info 符号类型和绑定属性
         *          STB_GLOBAL - 全局符号
         *
         *  最终这里对应的是链接的动态库中的函数 
         */
		if (s->st_shndx == SHN_UNDEF &&
		    GELF_ST_BIND(s->st_info) == STB_GLOBAL) {
			count++;
            //[kpatch_count_undefined:697] Undefined symbol 'puts@@GLIBC_2.2.5'
            //[kpatch_count_undefined:697] Undefined symbol 'printf@@GLIBC_2.2.5'
			kpdebug("Undefined symbol '%s'\n", strsym + s->st_name);
			info_log("Undefined symbol '%s'\n", strsym + s->st_name);
		}
	}
    warn_log("Undefined symbol total %d\n", count);
	return count;
}

static int
sym_name_cmp(const void *a_, const void *b_, void *s_)
{
	const Elf64_Sym *a = (const Elf64_Sym *)a_;
	const Elf64_Sym *b = (const Elf64_Sym *)b_;
	const char *s = (char *)s_;
	int rv, t;

	/*
	 * Sort references to undefined symbols to be at the end
	 * so we can later cut them off.
	 */
	t = is_undef_symbol(a);

	rv = t - is_undef_symbol(b);
	if (rv)
		return rv;

	/* Make sure we are correctly sortable if both are undefined */
	if (!rv && t)
		return a->st_name - b->st_name;

	return strcmp(s + a->st_name, s + b->st_name);
}

/**
 *  
 */
static int
elf_object_load_dynsym(struct object_file *o)
{
	int rv;
	size_t i;
	Elf64_Dyn *dynamics = NULL;
	char *buffer = NULL;
	Elf64_Phdr *phdr;
	unsigned long symtab_addr, strtab_addr;
	unsigned long symtab_sz, strtab_sz;

	if (o->dynsyms != NULL)
		return 0;

	rv = elf_object_peek_phdr(o);
	if (rv < 0)
		return rv;

    /**
     *  找到动态库的程序头
     */
	for (i = 0; i < o->ehdr.e_phnum; i++) {
		if (o->phdr[i].p_type == PT_DYNAMIC)
			break;
	}

    /**
     *  没找到
     */
	if (i == o->ehdr.e_phnum)
		return -1;

    /**
     *  动态库程序头
     */
	phdr = &o->phdr[i];

    /**
     *  分配这个动态库 segment 大小
     */
	dynamics = malloc(phdr->p_memsz);
	if (dynamics == NULL)
		return -1;

    /**
     *  从 
     */
	rv = kpatch_process_mem_read(o->proc,
				     o->load_offset + phdr->p_vaddr,
				     dynamics,
				     phdr->p_memsz);
	if (rv < 0)
		goto out_free;

    /**
     *  遍历所有 动态 segment
     */
	for (i = 0; i < phdr->p_memsz / sizeof(Elf64_Dyn); i++) {
		Elf64_Dyn *curdyn = dynamics + i;
		switch (curdyn->d_tag) {
		case DT_SYMTAB:
			symtab_addr = curdyn->d_un.d_ptr;
			break;
		case DT_STRTAB:
			strtab_addr = curdyn->d_un.d_ptr;
			break;
		case DT_STRSZ:
			strtab_sz = curdyn->d_un.d_val;
			break;
		case DT_SYMENT:
			if (sizeof(Elf64_Sym) != curdyn->d_un.d_val) {
				kperr("Dynsym entry size is %ld expected %ld\n",
				      curdyn->d_un.d_val, sizeof(Elf64_Sym));
				goto out_free;
			}
			break;
		}
	}

    /**
     *  
     */
	symtab_sz = (strtab_addr - symtab_addr);

	buffer = malloc(strtab_sz + symtab_sz);
	if (buffer == NULL)
		goto out_free;

	rv = kpatch_process_mem_read(o->proc,
				     symtab_addr,
				     buffer,
				     strtab_sz + symtab_sz);
	if (rv < 0)
		goto out_free;

    debug_log("buffer = %s\n", buffer);
    
	o->dynsyms = (Elf64_Sym*) buffer;
	o->ndynsyms = symtab_sz / sizeof(Elf64_Sym);
	o->dynsymnames = malloc(sizeof(char *) * o->ndynsyms);

	qsort_r((void *)o->dynsyms, o->ndynsyms, sizeof(Elf64_Sym),
		sym_name_cmp, buffer + symtab_sz);

	for (i = 0; i < o->ndynsyms; i++) {
		if (is_undef_symbol(&o->dynsyms[i]))
			break;
		o->dynsymnames[i] = buffer + symtab_sz + o->dynsyms[i].st_name;
	}
	o->ndynsyms = i;


out_free:
	if (rv < 0)
		free(buffer);
	free(dynamics);

	return rv;
}

/* TODO reuse kpatch_cc */
static int
bsearch_strcmp(const void *a_, const void *b_)
{
	const char *a = (const char *)a_;
	const char *b = *(const char **)b_;

	return strcmp(a, b);
}

/**
 *  
 */
int kpatch_resolve_undefined_single_dynamic(struct object_file *o,
					    const char *sname,
					    unsigned long *addr)
{
	int rv;
	void *found;
	size_t n;

    /**
     *  
     */
	rv = elf_object_load_dynsym(o);
	if (rv < 0)
		return rv;

	found = bsearch(sname, o->dynsymnames,
			o->ndynsyms, sizeof(char *),
			bsearch_strcmp);
	if (found == NULL)
		return -1;

	n = (unsigned long)(found - (void *)o->dynsymnames) / sizeof(char *);

	*addr = o->dynsyms[n].st_value;
	return GELF_ST_TYPE(o->dynsyms[n].st_info);
}

/**
 *  printf@@GLIBC_2.2.5
 */
static unsigned long
kpatch_resolve_undefined(struct object_file *obj,
			 char *sname)
{
	struct object_file *o;
	unsigned long addr = 0;
	int type;
	char *p;

	/* TODO: versioned symbols which are ignored by now */
	p = strchr(sname, '@');
	if (p)
		*p = 0;

	/*
	 * TODO: we should do this in the same order as linker does.
	 * Otherwise we might end up picking up the wrong symbol!!!
	 */
	list_for_each_entry(o, &obj->proc->objs, list) {
		if (!o->is_shared_lib)
			continue;

        /**
         *  
         */
		type = kpatch_resolve_undefined_single_dynamic(o, sname, &addr);
		if (type == -1)
			continue;

        unsigned long _addr = addr;
		addr = vaddr2addr(o, addr);

        debug_log("vaddr2addr: sname=%s 0x%016lx -> 0x%016lx\n", sname, _addr, addr);
        /**
         *  I - 表示间接
         *  TODO - 2021年9月22日09:23:23
         */
		if (type == STT_GNU_IFUNC) {
            debug_log("STT_GNU_IFUNC.\n");
			if (kpatch_ptrace_resolve_ifunc(proc2pctx(obj->proc), &addr) < 0)
				kpfatalerror("kpatch_ptrace_resolve_ifunc failed\n");
        }
		break;
	}

	return addr;
}

#define JMP_TABLE_JUMP  0x90900000000225ff /* jmp [rip+2]; nop; nop */
/**
 *  
 */
static unsigned long kpatch_add_jmp_entry(struct object_file *o, unsigned long addr)
{
	struct kpatch_jmp_table_entry entry = {JMP_TABLE_JUMP, addr};
	int e;

	if (o->jmp_table == NULL) {
		kpfatalerror("JMP TABLE not found\n");
		return 0;
	}

	if (o->jmp_table->cur_entry >= o->jmp_table->max_entry)
		return 0;
	e = o->jmp_table->cur_entry++;
	o->jmp_table->entries[e] = entry;
	return (unsigned long)(o->kpta + o->kpfile.patch->jmp_offset + \
			((void *)&o->jmp_table->entries[e] - (void *)o->jmp_table));
}

/**
 *  TODO 荣涛 2021年9月18日21:21:17
 *
 *  
 */
static inline int
symbol_resolve(struct object_file *o,
	       GElf_Shdr *shdr,
	       GElf_Sym *s,
	       char *symname)
{
	unsigned long uaddr;

    /**
     *  st_info - 指定符号类型及绑定属性
     *  GELF_ST_TYPE - 从 st_info 值中提取类型值
     */
	switch(GELF_ST_TYPE(s->st_info)) {
    /**
     *  
     */    
	case STT_SECTION:
		s->st_value = shdr[s->st_shndx].sh_addr;
		break;
    /**
     *  该符号类型于函数或者其他可执行代码关联
     */ 
	case STT_FUNC:
    /**
     *  表示该符号与数据目标文件关联
     */ 
	case STT_OBJECT:

        //38: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@@GLIBC_2.2.5
        //39: 00000000000000e6    17 FUNC    GLOBAL DEFAULT   14 print_hello
        //40: 0000000000000000    27 FUNC    GLOBAL DEFAULT   16 print_hello.kpatch
		/* TODO(pboldin) this breaks rule for overriding
		 * symbols via dynamic libraries. Fix it. */
		/**
         *  UNDEF - 动态库中的 printf 即为 undef
         */
		if (s->st_shndx == SHN_UNDEF &&
		    GELF_ST_BIND(s->st_info) == STB_GLOBAL) {
			/* This is a reference to a symbol from
			 * the dynamic library. Resolve it. */
            /**
             *  printf@@GLIBC_2.2.5
             */
			uaddr = kpatch_resolve_undefined(o, symname);

			if (!uaddr) {
				kperr("Failed to resolve undefined symbol '%s'\n",
				      symname);
				return -1;
			}
            /**
             *  
             */
			/* OK, we overuse st_size to store original offset */
			s->st_size = uaddr;
            /**
             *  
             */
			s->st_value = kpatch_add_jmp_entry(o, uaddr);

			kpdebug("symbol '%s' = 0x%lx\n", symname, uaddr);
			kpdebug("jmptable '%s' = 0x%lx\n", symname, s->st_value);
		} 
        /**
         *  
         */
        else {
			/*
			 * We retain all non-local (except for .LC*)
			 * symbols to help us debugging.
			 */
			if (GELF_ST_BIND(s->st_info) == STB_GLOBAL) {
				kpwarn("symbol '%s' is defined and global, we don't check for overrition\n", symname);
				warn_log("symbol '%s' is defined and global, we don't check for overrition\n", symname);
            }

            /**
             *  sh_addr - section 的起始地址
             *  st_shndx - 每个符号表条目的定义都与某些节对应，该变量保存了相关节头索引
             *  st_value - 存放符号的值，可能是地址或者位置偏移量
             */
			s->st_value += shdr[s->st_shndx].sh_addr;

            /**
             *  print_hello
             *  print_hello.kpatch
             */
			kpdebug("symbol '%s' = 0x%lx\n", symname, s->st_value);
			debug_log(">> symbol '%s' = 0x%lx\n", symname, s->st_value);
		}

		break;

	case STT_TLS:
		break;

	case STT_NOTYPE:			// for Systemtap symbol _.stapsdt.base.kpatch
		break;

	default:
		kperr("Unsupported symbol type: %d\n", GELF_ST_TYPE(s->st_info));
		return -1;
	}

	return 0;
}

/**
 *  
 */
int kpatch_resolve(struct object_file *o)
{
    /**
     *  文件头，section 头
     */
	GElf_Ehdr *ehdr;
	GElf_Shdr *shdr;
	GElf_Sym *sym;
	int i, symidx, rv;
	char *strsym;

    /**
     *  获取 补丁 ELF 文件映射的首地址，这个地址即为 ELF header
     */
	ehdr = (void *)o->kpfile.patch + o->kpfile.patch->kpatch_offset;
    /**
     *  e_shoff 为 section的首地址偏移量
     */
	shdr = (void *)ehdr + ehdr->e_shoff;

	kpdebug("Resolving sections' addresses for '%s'\n", o->name);

    /**
     *  遍历所有 section header
     */
	for (i = 1; i < ehdr->e_shnum; i++) {
        /**
         *  获取 section header 
         */
		GElf_Shdr *s = shdr + i;
        /**
         *  如果是 symbol table
         */
		if (s->sh_type == SHT_SYMTAB)
			symidx = i;

        /**
         *  TODO
         */
		if (kpatch_is_our_section(s)) {
			/*
			 * For our own sections, we just point sh_addr to
			 * proper offet in *target process* region of memory
			 *
			 * kpta 保存了 patch 文件的初始地址，这个地址重定向到我们的补丁中
			 */
			s->sh_addr = (unsigned long)o->kpta +
				    o->kpfile.patch->kpatch_offset + s->sh_offset;
            err_log("Our section : %s.\n", secname(ehdr, s));
		} else {
			/*
			 * We copy the `sh_addr`esses from the original binary
			 * into the patch during the preparation. Just use
			 * this.
			 */
			if (s->sh_addr)
				s->sh_addr += (unsigned long)o->load_offset;
            err_log("Wrong section : %s.\n", secname(ehdr, s));
		}
		kpdebug("section '%s' = 0x%lx\n", secname(ehdr, s), s->sh_addr);
	}

	kpdebug("Resolving symbols for '%s'\n", o->name);

    /**
     *  符号表 section header
     */
	sym = (void *)ehdr + shdr[symidx].sh_offset;
//    err_log("Wrong section : %s.\n", secname(ehdr, s));
    /**
     *  获取符号表 section
     */
	strsym = (void *)ehdr + shdr[shdr[symidx].sh_link].sh_offset;
    /**
     *  
     */
	for (i = 1; i < shdr[symidx].sh_size / sizeof(GElf_Sym); i++) {
		GElf_Sym *s = sym + i;
		char *symname = strsym + s->st_name;
    
        //[kpatch_resolve:1088] symname: .
        //[kpatch_resolve:1088] symname: .
        //[kpatch_resolve:1088] symname: .
        //[kpatch_resolve:1088] symname: .
        //[kpatch_resolve:1088] symname: puts@@GLIBC_2.2.5.
        //[kpatch_resolve:1088] symname: print_hello2.
        //[kpatch_resolve:1088] symname: printf@@GLIBC_2.2.5.
        //[kpatch_resolve:1088] symname: print_hello.
        //[kpatch_resolve:1088] symname: print_hello.kpatch.
        err_log("symname: %s.\n", symname);
        
        /**
         *  
         */
		rv = symbol_resolve(o, shdr, s, symname);
		if (rv < 0)
			return rv;
	}

	return 0;
}

/**
 *  
 *  重定向 .rela.kpatch.info
 */
static int kpatch_apply_relocate_add(struct object_file *o, GElf_Shdr *relsec)
{
    /**
     *  
     */
	struct kpatch_file *kp = o->kpfile.patch;
    /**
     *  程序头
     */
	GElf_Ehdr *ehdr = (void *)kp + kp->kpatch_offset;
    /**
     *  section头
     */
	GElf_Shdr *shdr = (void *)ehdr + ehdr->e_shoff, *symhdr;
    /**
     *  重定向 .rela.kpatch.info segment
     *  .rela.kpatch.info 在 ELF 文件中的位置
     */
	GElf_Rela *relocs = (void *)ehdr + relsec->sh_offset;
    /**
     *  重定向 .rela.kpatch.info 节头
     */
	GElf_Shdr *tshdr = shdr + relsec->sh_info;
    debug_log("relsec->sh_info = %016lx\nrelsec->sh_offset = %016lx\n", relsec->sh_info, relsec->sh_offset);
    /**
     *  offset of shdr from beginning of file
     *  当前进程
     */
	void *t = (void *)ehdr + tshdr->sh_offset;
    /**
     *  address of where is section begins
     *  被追踪的进程
     */
	void *tshdr2 = (void *)tshdr->sh_addr;


    debug_log("tshdr->sh_addr = %016lx\ntshdr->sh_offset = %016lx\n", tshdr->sh_addr, tshdr->sh_offset);
    
	int i, is_kpatch_info;
	const char *scnname;

    /**
     *  找到 symbol section
     */
	for (i = 1; i < ehdr->e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			symhdr = &shdr[i];
            /**
             *  + break;  rongtao 2021年9月22日09:47:55
             */
            break; 
        }
	}
    
    
    /**
     *  .kpatch.text
     *  .kpatch.info
     */
	scnname = secname(ehdr, shdr + relsec->sh_info);
	kpdebug("applying relocations to '%s'\n", scnname);
	debug_log("applying relocations to '%s'\n", scnname);
    
	is_kpatch_info = strcmp(scnname, ".kpatch.info") == 0;

    /**
     *  遍历
     */
	for (i = 0; i < relsec->sh_size / sizeof(*relocs); i++) {
        /**
         *  
         */
		GElf_Rela *r = relocs + i;
		GElf_Sym *s;
		unsigned long val;
		void *loc, *loc2;

        /**
         *  
         */
		if (r->r_offset < 0 || r->r_offset >= tshdr->sh_size)
			kpfatalerror("Relocation offset for section '%s'"
				     " is at 0x%lx beyond the section size 0x%lx\n",
				     scnname, r->r_offset, tshdr->sh_size);

        /**
         *  当前进程的地址空间
         */
		/* Location in our address space */
		loc = t + r->r_offset;
        /**
         *  被追踪的进程地址空间
         */
		/* Location in target process address space (for relative addressing) */
		loc2 = tshdr2 + r->r_offset;

        /**
         *  r_info 包含了符号表索引 和 重定位类型
         */
		s = (GElf_Sym *)((void *)ehdr + symhdr->sh_offset) + GELF_R_SYM(r->r_info);
        /**
         *  st_value - 存放符号的值，可能是 地址或者位置偏移量
         *  r_addend - 用于计算存储在可重定位字段中的值
         */
		val = s->st_value + r->r_addend;
        
        debug_log("s->st_value = %016lx\n", s->st_value);
        debug_log("r->r_addend = %016lx\n", r->r_addend);
        
        /**
         *  .kpatch.info
         */
		if (is_kpatch_info && is_undef_symbol(s)) {
			val = s->st_size;
		}

        /**
         *  重定位类型
         *  如果 做 ARM 兼容， 需要考虑 R_ARM_NONE ？？ 
         *  荣涛 2021年9月22日11:09:52
         */
		switch (GELF_R_TYPE(r->r_info)) {
		case R_X86_64_NONE:
			break;
		case R_X86_64_64:
			*(unsigned long *)loc = val;
			break;
		case R_X86_64_32:
			*(unsigned int *)loc = val;
			break;
		case R_X86_64_32S:
			*(signed int *)loc = val;
			break;
		case R_X86_64_GOTTPOFF:
		case R_X86_64_GOTPCREL:
        /* Load from 32 bit signed pc relative
           offset to GOT entry with REX prefix,
           relaxable.  */    
		case R_X86_64_REX_GOTPCRELX:
        /* Load from 32 bit signed pc relative
           offset to GOT entry without REX
           prefix, relaxable.  */
		case R_X86_64_GOTPCRELX:
			if (is_undef_symbol(s)) {
				/* This is an undefined symbol,
				 * use jmp table as the GOT */
				val += sizeof(unsigned long);
			} else if (GELF_ST_TYPE(s->st_info) == STT_TLS) {
				/* This is GOTTPOFF that already points
				 * to an appropriate GOT entry in the
				 * patient's memory.
				 */
				val = r->r_addend + o->load_offset - 4;
			}
			/* FALLTHROUGH */
		case R_X86_64_PC32:
			val -= (unsigned long)loc2;
			*(unsigned int *)loc = val;
			break;
		case R_X86_64_TPOFF64:
		case R_X86_64_TPOFF32:
			kperr("TPOFF32/TPOFF64 should not be present\n");
			break;
		default:
			kperr("unknown relocation type: %lx\n", r->r_info);
			return -1;
		}
	}

	return 0;
}

/**
 *  重定位问题
 */
int kpatch_relocate(struct object_file *o)
{
    /**
     *  
     */
	GElf_Ehdr *ehdr;
	GElf_Shdr *shdr;
	int i, ret = 0;

    /**
     *  程序头
     */
	ehdr = (void *)o->kpfile.patch + o->kpfile.patch->kpatch_offset;
    /**
     *  section 头
     */
	shdr = (void *)ehdr + ehdr->e_shoff;

	kpdebug("Applying relocations for '%s'...\n", o->name);
    /**
     *  遍历所有 section头
     */
	for (i = 1; i < ehdr->e_shnum; i++) {
		GElf_Shdr *s = shdr + i;

        /**
         *  重定向 .rela.kpatch.info
         */
		if (s->sh_type == SHT_RELA)
			ret = kpatch_apply_relocate_add(o, s);
        /**
         *  
         */
		else if (shdr->sh_type == SHT_REL) {
			kperr("TODO: handle SHT_REL\n");
			return -1;
		}
		if (ret)
			return -1;
	}

	return 0;
}

/**
 *  加载 kpatch info
 */
int kpatch_elf_load_kpatch_info(struct object_file *o)
{
	GElf_Ehdr *ehdr;
	GElf_Shdr *shdr;
	int i;

	if (o->info != NULL)
		return 0;

	ehdr = (void *)o->kpfile.patch + o->kpfile.patch->kpatch_offset;
    /**
     *  读取 section header 头，第一个 section
     */
	shdr = (void *)ehdr + ehdr->e_shoff;
    
    //
    //    .pushsection .kpatch.info,"a",@progbits
    //print_hello.Lpi:
    //    .quad print_hello
    //    .quad print_hello.kpatch
    //    .long print_hello.Lfe - print_hello
    //    .long print_hello.kpatch_end - print_hello.kpatch
    //    .quad kpatch_strtab1
    //    .quad 0
    //    .long 0
    //    .byte 0, 0, 0, 0
    //    .popsection
//	kpdebug("Loading patch info '%s'...", o->name);
	warn_log("Loading patch info '%s'...\n", o->name);
    /**
     *  section header 的数量
     */
	for (i = 1; i < ehdr->e_shnum; i++) {
		GElf_Shdr *s = shdr + i;
        /**
         *  如果是 .kpatch.info
         *
        //	.pushsection .kpatch.info,"a",@progbits
        //print_hello.Lpi:
        //	.quad print_hello
        //	.quad print_hello.kpatch
        //	.long print_hello.Lfe - print_hello
        //	.long print_hello.kpatch_end - print_hello.kpatch
        //	.quad kpatch_strtab1
        //	.quad 0
        //	.long 0
        //	.byte 0, 0, 0, 0
        //	.popsection         
         */
		if (!strcmp(secname(ehdr, s), ".kpatch.info")) {
            /**
             *  读取这个 section 存放的内存
             *  这个数据结构 和 在 foobar.s 中添加的 section 相对应
             */
			o->info = (struct kpatch_info *)((void *)ehdr + s->sh_offset);
            /**
             *  section 大小/ 头大小 得到info个数，
             *  假如我的测试例中只修改了 print_hello()函数，那么这里将只有一个
             */
			o->ninfo = s->sh_size / sizeof(struct kpatch_info);
			info_log("successfully, %ld entries\n", o->ninfo);
			return 0;
		}
	}

	kpdebug("failed\n");
	return -1;
}
