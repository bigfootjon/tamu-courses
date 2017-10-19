#ifndef _bounded_buffer_h_
#define _bounded_buffer_h_

#include "semaphore.H"

template <class T>
class BoundedBuffer {
private:
	int n;
	T *buffer;
	int push_index;
	int pop_index;
	Semaphore mutex;
	Semaphore empty;
	Semaphore full;
public:
	BoundedBuffer(int _n);
	~BoundedBuffer();
	
	void push(T item);
	T pop();
};

#endif
