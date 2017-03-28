; Metadata:
	.file	"lab5_prob3_1.c"
	.section	.rodata
; Static things
.LC0:
	.string	"Hello, world"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
; The following 2 lines print out "Hello, world" by reading it from .LC0 and calling "puts"
	movl	$.LC0, %edi
	call	puts 
; The following lines (until "ret") set the return value and then return from the function 
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
; This area contains more metadata
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.0"
	.section	.note.GNU-stack,"",@progbits
