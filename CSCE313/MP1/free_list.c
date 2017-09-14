#include "free_list.h"


FL_HEADER* FL_add(FL_HEADER *free_list, FL_HEADER *block) {
	free_list->previous = block;
	block->next = free_list;
	return block;
}

void FL_remove(FL_HEADER *free_list, FL_HEADER *block) {
	if (block->previous != 0) {
		block->previous->next = block->next;
	}
	if (block->next != 0) {
		block->next->previous = block->previous;
	}
}

FL_HEADER* FL_init(void* raw_pointer, int length) {
	FL_HEADER* pointer = (FL_HEADER*)raw_pointer;
	pointer->next = 0;
	pointer->previous = 0;
	pointer->length = length - sizeof(FL_HEADER);
	return pointer;
}
