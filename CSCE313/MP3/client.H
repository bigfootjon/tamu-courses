#ifndef _client_h_
#define _client_h_

#include "bounded_buffer.H"

struct ThreadDetails {
	std::string name;
	BoundedBuffer * buffer;
};

void * request_thread(void * attr);
void * worker_thread(void * attr);
void * stat_thread(void * attr);

#endif
