#include "free_list.h"


FL_HEADER* FL_add(FL_HEADER *free_list, FL_HEADER *block) {
	block->free = true;
	if (free_list == 0) {
		return block;
	}
	free_list->previous = block;
	block->next = free_list;
	return block;
}

FL_HEADER* FL_remove(FL_HEADER *free_list, FL_HEADER *block) {
	block->free = false;
	if (free_list == block) {
		return 0;
	}
	if (block->previous != 0) {
		block->previous->next = block->next;
	}
	if (block->next != 0) {
		block->next->previous = block->previous;
	}
	return free_list;
}

FL_HEADER* FL_init(Addr raw_pointer, unsigned int length) {
	FL_HEADER* pointer = (FL_HEADER*)raw_pointer;
	pointer->next = 0;
	pointer->previous = 0;
	pointer->length = length;
	pointer->free = false;
	return pointer;
}
