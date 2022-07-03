# Metadata
	.file	"lab5_prob3_2.c"
	.section	.rodata
# Static store of string
.LC0:
	.string	"The value of i is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
# begin setup of function
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
# Create the variable i and assign 1 to it
	movl	$1, -4(%rbp)
# Increment i by 1
	addl	$1, -4(%rbp)
# Set up the call to printf
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
# Call printf
	call	printf
# Setup the return value
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
# Return from main function
	ret
	.cfi_endproc
# Begin other metadata
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.3.0"
	.section	.note.GNU-stack,"",@progbits
