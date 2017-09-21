/* 
    File: my_allocator.c

    Author: Jonathan Janzen
            Department of Computer Science
            Texas A&M University
    Date  : 7 September 2017

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

#include <stdlib.h>
#include <stdio.h>
#include "my_allocator.h"
#include "free_list.h"

char* base; // This is used to release the entire block of memory instead of wherever start is pointing to right now 
FL_HEADER* start;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length) {
	if (start == 0) {
		base = (char*)malloc(_length);
		if (base == 0) {
			return 0;
		}
		start = FL_init(base, _length);
	}
	return _length;
}

Addr my_malloc(size_t _length) {
	if (start == 0) {
		return 0;
	}
	FL_HEADER* current = start;
	while (current != 0) {
		if (current->length >= _length) {
			break;
		}
		current = start->next;
	}
	if (current == 0) {
		return 0;
	}
	start = FL_remove(start, current);
	if (_length + 2 * sizeof(FL_HEADER) < current->length) {
		unsigned int extra_space = current->length - _length - sizeof(FL_HEADER);
		FL_HEADER* new_header = FL_init((char*)current + _length + sizeof(FL_HEADER), extra_space);
		current->length = _length - sizeof(FL_HEADER);
		start = FL_add(start, new_header);
	}
	return (Addr)(((char*)current) + sizeof(FL_HEADER));
}

int my_free(Addr _a) {
	FL_HEADER* header = (FL_HEADER*)((char*)_a - sizeof(FL_HEADER));
	header->next = 0;
	header->previous = 0;
	start = FL_add(start, header);
	return 0;
}

int release_allocator() {
	free(base);
	return 0;
}

