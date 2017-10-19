#include "bounded_buffer.H"

template <class T>
BoundedBuffer<T>::BoundedBuffer(int _n) {
	n = _n;
	buffer = new T[n];
	push_index = 0;
	pop_index = 0;
	mutex(1);
	full(0);
	empty(n);
}

template <class T>
BoundedBuffer<T>::~BoundedBuffer() {
	delete buffer;
}

template <class T>
void BoundedBuffer<T>::push(T item) {
	empty.P();
	mutex.P();
	
	mutex.V();
	full.V();
}

template <class T>
T BoundedBuffer<T>::pop() {
	full.P();
	mutex.P();
	// POP HERE:
	T item;
	mutex.V();
	empty.V();
	return item;
}
