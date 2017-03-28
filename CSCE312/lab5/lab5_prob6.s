	.file	"lab5_prob6.c"
	.text
	.globl	very_fast_function
	.type	very_fast_function, @function
very_fast_function:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	sall	$6, %eax
	addl	$1, %eax
	cmpl	$1024, %eax
	jle	.L2
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	very_fast_function, .-very_fast_function
	.section	.rodata
	.align 8
.LC0:
	.string	"The function value of i is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$40, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	very_fast_function
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.0"
	.section	.note.GNU-stack,"",@progbits
