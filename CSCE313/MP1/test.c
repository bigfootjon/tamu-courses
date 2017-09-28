#include <stdio.h>
#include <stdlib.h>

#include "my_allocator.h"
#include "free_list.h"

int main(int arv, char** argc) {
	printf("Initializing allocator with 128 bytes (bbs=4): %x\n", init_allocator(4, 128));
	printf("Size of FL_HEADER: %x\n", (unsigned int)sizeof(FL_HEADER));
	void* pointer1 = my_malloc(1);
	printf("Allocate memory(1): %x\n", (unsigned int)pointer1);
	void* pointer2 = my_malloc(2);
	printf("Allocate memory(2): %x\n", (unsigned int)pointer2);
	printf("Allocate memory(L): %x\n", (unsigned int)my_malloc(100));
	/*printf("Free     memory(2): %x\n", my_free(pointer2));
	printf("Allocate memory(2): %x\n", (unsigned int)my_malloc(2));
*/
	release_allocator();
}
