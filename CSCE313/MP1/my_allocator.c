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

const int MEMORY_SIZE = 200000000;

char* start;
unsigned int remaining;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length) {
	if (start == NULL) {
		start = (char*)malloc(_length);
		if (start == NULL) {
			return 0;
		}
		remaining = _length;
	}
	return _length;
}

Addr my_malloc(size_t _length) {
	if (start == NULL) {
		return NULL;
	}
	if (remaining < _length) {
		return NULL;
	} else {
		Addr allocated = (Addr)start;
		start += _length;
		remaining -= _length;
		return allocated;
	}
}

int my_free(Addr _a) {
	return 0;
}

int release_allocator() {
	return 0;
}

