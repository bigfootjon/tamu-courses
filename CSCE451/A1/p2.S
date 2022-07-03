.globl _main
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
	
	//PROBLEM 2 PART 2:
	mov %rbx, %rcx // Since values were popped off the stack low to high, we can reuse the last popped value as the number of values that were in the stack
	div %rcx // See division setup above (i.e. %rdx still contains 0), after this division, rax contains the average (17)

	//PROBLEM 2 PART 3:
	mov %rbx, %rcx
l3:
	push %rcx
	dec %rcx
	jnz l3

	mov %rbx, %rcx
	mov $0, %rax
l4:
	pop %rbx
	mov $20, %rdx
	cmpq %rbx, %rdx
	jb l4body
	mov $30, %rdx
	cmpq %rdx, %rbx
	jb l4end
l4body:
	add %rbx, %rax
l4end:
	dec %rcx
	jnz l4

	mov $0, %rdx
	mov $24, %rcx
	div %rcx

	//PROBLEM 2 PART 4:
	mov $33, %rdx
	sub $1, %rdx
	
	// Restore stack and end program
	pop %rbp
	ret
