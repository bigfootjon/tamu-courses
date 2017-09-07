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

const int MEMORY_SIZE = 1000000000;

Addr base;
unsigned int remaining;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length) {
	if (base == NULL) {
		base = malloc(_length);
		remaining = _length;
	}
	return _length;
}

Addr my_malloc(size_t _length) {
	if (base == NULL) {
		printf("Allocating memory");
		init_allocator(0, MEMORY_SIZE);
	}
	if (remaining < _length) {
		return NULL;
	} else {
		Addr allocated = base;
		base += _length;
		remaining -= _length;
		return allocated;
	}
}

int my_free(Addr _a) {
	return 0;
}

