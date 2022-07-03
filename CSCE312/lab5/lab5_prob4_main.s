# Begin metadata
	.file	"lab5_prob4_main.c"
	.text
# Define exportable function "main"
	.globl	main
	.type	main, @function
# Setup main function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
# Setup parameters
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
# Setup call to print_hello
	movl	$0, %eax
# Call print_hello
	call	print_hello
# Setup return value
	movl	$0, %eax
# Return from main (through line with "ret")
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
# Metadata for main function
.LFE0:
	.size	main, .-main
	.section	.rodata
# Static data for hello_world
.LC0:
	.string	"Hello, world"
	.text
# Declaring print_hello function
	.globl	print_hello
	.type	print_hello, @function
# Setup print_hello function
print_hello:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
# Move static data "Hello, world" into register
	movl	$.LC0, %edi
# Call puts with the string copied in the previous line
	call	puts
# Prepare to return
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
# Return
	ret
	.cfi_endproc
# Metadata for print_hello
.LFE1:
	.size	print_hello, .-print_hello
	.ident	"GCC: (GNU) 6.3.0"
	.section	.note.GNU-stack,"",@progbits
