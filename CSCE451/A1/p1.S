.globl _main

.text
_main:
	// Set up stack
	push %rbp
	mov %rsp, %rbp
	
	// Set up variables
	mov $0, %rdx // Set higher bits of dividend to 0
	mov $0, %rax // Set initial sum to 0, will be used as dividend
	mov $5, %rcx // Set divisor to 5 (number of values)
	
	// Push values
	push $4
	push $77
	push $18
	push $57
	push $9
	
	// Pop and perform additions
	pop %rbx
	add %rbx, %rax
	pop %rbx
	add %rbx, %rax
	pop %rbx
	add %rbx, %rax
	pop %rbx
	add %rbx, %rax
	pop %rbx
	add %rbx, %rax

	// Perform division (%rdx:%rax / %rcx = %rax)
	div %rcx
	
	// Restore stack and end program
	pop %rbp
	ret
