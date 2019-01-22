.globl _main
.text
_main:
	// Set up stack
	push %rbp
	mov %rsp, %rbp

	//PROBLEM 3 PART 1
	mov $0, %rax
	mov $101, %rbx
l1:
	push %rax
	inc %rax // <-- PROBLEM 3 PART 2
	mov $42, %rcx
	cmpq %rax, %rcx
	jne l1end
	push $42
	push $42
	push $42
	push $42
	push $42
	push $42
	push $42
	push $42
	push $42
l1end:
	dec %rbx
	jnz l1

	//PROBLEM 3 PART 3
	mov $110, %rbx
	mov $0, %rcx
l2:
	pop %rdx
	mul %rdx
	add %rdx, %rcx // <-- PROBEM 3 PART 4 (stored in %rcx)
	dec %rbx
	jnz l2
	
	// Restore stack and end program
	pop %rbp
	ret
