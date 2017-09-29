#include <stdio.h>
#include <stdlib.h>

#include "my_allocator.h"
#include "free_list.h"

int main(int arv, char** argc) {
	printf("Initializing allocator with 256 bytes (bbs=4): %d\n", init_allocator(32, 1056));
	printf("Size of FL_HEADER : %ld\n", (long)sizeof(FL_HEADER));
	void* pointer1 = my_malloc(1);
	printf("Allocate memory(1) : %ld\n", (long)pointer1);
	void* pointer2 = my_malloc(2);
	printf("Allocate memory(2) : %ld\n", (long)pointer2);
	void* long1 = my_malloc(100);
	printf("Allocate memory(L) : %ld\n", (long)long1);
	printf("Free     memory(2) : %d\n", my_free(pointer2));
	pointer2 = my_malloc(2);
	printf("Allocate memory(2) : %ld\n", (long)pointer2);
	printf("Free     memory(1) : %d\n", my_free(pointer1));
	printf("Free     memory(2) : %d\n", my_free(pointer2));
	printf("Free     memory(L) : %d\n", my_free(long1));
	release_allocator();
}
