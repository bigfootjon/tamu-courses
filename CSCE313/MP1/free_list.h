#ifndef _free_list_h_
#define _free_list_h_

#include "my_allocator.h"

struct fl_header {
	unsigned int length;
	struct fl_header *previous;
	struct fl_header *next;
};

typedef struct fl_header FL_HEADER;

FL_HEADER* FL_remove(FL_HEADER *free_list, FL_HEADER *block);

FL_HEADER* FL_add(FL_HEADER *free_list, FL_HEADER *block);

FL_HEADER* FL_init(Addr raw_pointer, unsigned int length);

#endif
