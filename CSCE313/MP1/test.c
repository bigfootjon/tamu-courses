#include <stdio.h>
#include <stdlib.h>

#include "my_allocator.h"

int main(int arv, char** argc) {
	printf("100==%d\n", init_allocator(1, 100));
	printf("(some hex)==%x\n", (unsigned int)my_malloc(2));
	printf("(some hex)+2==%x\n", (unsigned int)my_malloc(1));
	printf("0==%x\n", (unsigned int)my_malloc(100));

	release_allocator();
}
