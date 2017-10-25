#ifndef _client_h_
#define _client_h_

#include "bounded_buffer.H"
#include "reqchannel.H"
#include <string>

struct RequestDetails {
	std::string name;
	BoundedBuffer * buffer;
	int * request_threads;
	int * request_count;

	RequestDetails(std::string _name, BoundedBuffer * _buffer, int * _request_threads, int * _request_count) :
		name(_name), buffer(_buffer), request_threads(_request_threads), request_count(_request_count) {}
};

struct WorkerDetails {
	BoundedBuffer * in_buffer;
	BoundedBuffer * out_buffer;
	RequestChannel * base_chan;
	int * worker_threads;
	
	WorkerDetails(BoundedBuffer * _in, BoundedBuffer * _out, RequestChannel * _base_chan, int * _worker_threads) :
		in_buffer(_in), out_buffer(_out), base_chan(_base_chan), worker_threads(_worker_threads) {}
};

struct StatsDetails {
	std::string name;
	BoundedBuffer * buffer;
	
	StatsDetails(std::string _name, BoundedBuffer * _buffer) : name(_name), buffer(_buffer) {}
};

void * request_thread(void * attr);
void * worker_thread(void * attr);
void * stat_thread(void * attr);

#endif
