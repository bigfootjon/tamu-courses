.globl _main
.data
format: .asciz "%u\n"
.text
_main:
	// PROBLEM 1
	// Set up stack
	push %rbp
	mov %rsp, %rbp
	
	mov $0, %rax // Set initial sum to 0, will be used as dividend
	
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
	mov $0, %rdx // Set higher bits of dividend to 0
	mov $5, %rcx // Set divisor to 5 (number of values)
	div %rcx

	//PROBLEM 2 PART 1:
	mov %rax, %rcx
l1:
	push %rcx
	dec %rcx
	jnz l1

	mov %rax, %rcx
	mov $0, %rax
l2:
	pop %rbx
	add %rbx, %rax
	dec %rcx
	jnz l2
	
	div %rcx
	
	// Restore stack and end program
	pop %rbp
	ret
