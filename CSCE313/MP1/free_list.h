struct fl_header {
	int length;
	struct fl_header *previous;
	struct fl_header *next;
};

typedef struct fl_header FL_HEADER;

void FL_remove(FL_HEADER *free_list, FL_HEADER *block);

FL_HEADER* FL_add(FL_HEADER *free_list, FL_HEADER *block);

FL_HEADER* FL_init(void* raw_pointer, int length);
