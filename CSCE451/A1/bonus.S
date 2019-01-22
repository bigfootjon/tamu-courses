.globl _main
.data
format: .asciz "Howdy!\n"
.text
_main:
	// set up stack
	push %rbp
	mov %rsp, %rbp

	leaq	format(%rip), %rdi
	mov	$0, %rsi
	movb	$0, %al
	callq	_printf
	mov $0, %eax
	
	// Restore stack and end program
	pop %rbp
	ret
