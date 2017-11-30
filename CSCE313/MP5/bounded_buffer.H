#ifndef _bounded_buffer_h_
#define _bounded_buffer_h_

#include "semaphore.H"

#include <string>

class BoundedBuffer {
private:
	int n;
	std::string *buffer;
	int push_index;
	int pop_index;
	Semaphore mutex;
	Semaphore empty;
	Semaphore full;
public:
	BoundedBuffer(int _n);
	~BoundedBuffer();
	
	void push(std::string item);
	std::string pop();
};

#endif
