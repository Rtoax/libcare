	.file	"foo.c"
	.text
	.section	.rodata
.LC0:
	.string	"hello world2."
	.text
	.globl	print_hello2
	.type	print_hello2, @function
print_hello2:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	call	puts
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	print_hello2, .-print_hello2
	.section	.rodata
.LC1:
	.string	"being patched"
.LC2:
	.string	"Hello world %s!\n"
	.text
	.globl	print_hello
	.type	print_hello, @function
print_hello:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	call	print_hello2
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	print_hello, .-print_hello
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
.L4:
	call	print_hello
	movl	$1, %edi
	movl	$0, %eax
	call	sleep
	jmp	.L4
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.4.1 20200928 (Red Hat 8.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
