#include <stdio.h>

int very_fast_function(int);

asm("\
very_fast_function:\
        pushq   %rbp;\
        movq    %rsp, %rbp;\
        movl    %edi, -4(%rbp);\
        movl    -4(%rbp), %eax;\
        sall    $6, %eax;\
        addl    $1, %eax;\
        cmpl    $1024, %eax;\
        jle     .L2;\
        movl    -4(%rbp), %eax;\
        leal    1(%rax), %edx;\
        movl    %edx, -4(%rbp);\
        jmp     .L3;\
.L2:\
        movl    $0, %eax;\
.L3:\
        popq    %rbp;\
        ret\
");

int main(int argc, char *argv[]) {
	int i;
	i = 40;
	printf("The function value of i is %d\n", very_fast_function(i) );
	return 0;
}
