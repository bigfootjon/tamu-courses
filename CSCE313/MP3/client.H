#ifndef _client_h_
#define _client_h_

#include "bounded_buffer.H"
#include "reqchannel.H"

struct RequestDetails {
	std::string name;
	BoundedBuffer * buffer;
	int * request_threads;
	int * worker_threads;
	int request_count;
};

struct WorkerDetails {
	BoundedBuffer * in_buffer;
	BoundedBuffer * out_buffer;
	RequestChannel * base_chan;
	int * worker_threads;
	int * stat_threads;
};

struct StatsDetails {
	std::string name;
	BoundedBuffer * buffer;
};

void * request_thread(void * attr);
void * worker_thread(void * attr);
void * stat_thread(void * attr);

#endif
