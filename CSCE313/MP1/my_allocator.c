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

typedef struct fl_tier {
	FL_HEADER* fl;
	unsigned int length;
} FL_TIER;

// This is used to release the entire block of memory instead of wherever start is pointing to right now
char* base;
unsigned int base_length;

int tiers = 0;
FL_TIER* fl_array;

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length) {
	if (fl_array == 0) {
		if (sizeof(FL_HEADER) > _basic_block_size) {
			// Make sure we have enough room for the FL_HEADER
			_basic_block_size = sizeof(FL_HEADER) + 1;
		}
		int nearest_pow = 1;
		while (nearest_pow < _basic_block_size) {
			nearest_pow *= 2;
		}
		_basic_block_size = nearest_pow;
		base = (char*)malloc(_length);
		if (base == 0) {
			return 0;
		}
		
		for (unsigned int i = _basic_block_size; i <= _length; i *= 2) {
			++tiers;
		}

		fl_array = (FL_TIER*)malloc(sizeof(FL_TIER) * tiers);
		
		unsigned int block_size = _basic_block_size;
		for (unsigned int i = 0; i < tiers; ++i) {
			fl_array[i].fl = 0;
			fl_array[i].length = block_size;
			block_size *= 2;
		}
		
		char* cur = base;
		bool done_adding = false;
		while (cur < base + _length && !done_adding) {
			for (int i = tiers - 1; i >= 0; --i) {
				if (base + _length - cur >= fl_array[i].length) {
					FL_HEADER* new_header = FL_init(cur, fl_array[i].length);
					fl_array[i].fl = FL_add(fl_array[i].fl, new_header);
					cur += fl_array[i].length;
					continue;
				}
				if (i == 0) {
					done_adding = true;
				}
			}
		}
		base_length = fl_array[tiers-1].length;
	}
	return _length;
}

FL_HEADER* get_block_at_tier(int tier) {
	if (tier > tiers) {
		return 0;
	}
	FL_HEADER* start = fl_array[tier].fl;
	if (start == 0) {
		start = get_block_at_tier(tier+1);
		if (start == 0) {
			return 0;
		}
		unsigned int new_length = start->length / 2;
		FL_HEADER* new_header = FL_init(((char*)start + new_length), new_length);
		fl_array[tier].fl = FL_add(fl_array[tier].fl, new_header);
		start = FL_init(start, new_length);
	} else {
		fl_array[tier].fl = FL_remove(fl_array[tier].fl, start);
	}
	return start;
}

Addr my_malloc(size_t _length) {
	if (fl_array == 0) {
		return 0;
	}
	int tier = 0;
	while (fl_array[tier].length - sizeof(FL_HEADER) < _length) ++tier;
	if (tier > tiers) {
		// Requesting more memory than we have, goodbye
		return 0;
	}
	FL_HEADER* allocated = get_block_at_tier(tier);
	if (allocated == 0) {
		return 0;
	} else {
		//printf("ALLOCATED: (%d)\n", allocated->length);
		//fl_print();
		return (Addr)(((char*)allocated) + sizeof(FL_HEADER));
	}
}

void merge_block(FL_HEADER* header) {
	int length = header->length;
	FL_HEADER* buddy = (FL_HEADER*)((((char*)header - base) ^ length) + base);
	FL_HEADER* lesser = header;
	if (buddy < header) {
		lesser = buddy;
	}
	if ((char*)lesser + 2 * lesser->length < (base + base_length) && buddy->free) {
		for (int i = 0; i < tiers; ++i) {
			if (fl_array[i].length == buddy->length) {
				fl_array[i].fl = FL_remove(fl_array[i].fl, buddy);
				break;
			}
		}
		lesser->length *= 2;
		merge_block(lesser);
	} else {
		for (int i = 0; i < tiers; ++i) {
			if (fl_array[i].length == header->length) {
				header->next = 0;
				header->previous = 0;
				fl_array[i].fl = FL_add(fl_array[i].fl, header);
				break;
			}
		}
	}
}

int my_free(Addr _a) {
	FL_HEADER* header = (FL_HEADER*)((char*)_a - sizeof(FL_HEADER));
	merge_block(header);
	//printf("FREED: (%d)\n", header->length);
	//fl_print();
	return 0;
}

int release_allocator() {
	free(base);
	return 0;
}

