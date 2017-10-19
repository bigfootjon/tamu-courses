#include "bounded_buffer.H"

using namespace std;

BoundedBuffer::BoundedBuffer(int _n) : mutex{1}, full{0}, empty{_n} {
	n = _n;
	buffer = new string[n];
	push_index = 0;
	pop_index = 0;
}

BoundedBuffer::~BoundedBuffer() {
	delete buffer;
}

void BoundedBuffer::push(string item) {
	empty.P();
	mutex.P();
	buffer[push_index] = item;
	if (++push_index >= n) {
		push_index = 0;
	}
	mutex.V();
	full.V();
}

string BoundedBuffer::pop() {
	full.P();
	mutex.P();
	string item = buffer[pop_index];
	if (++pop_index >= n) {
		pop_index = 0;
	}
	mutex.V();
	empty.V();
	return item;
}
