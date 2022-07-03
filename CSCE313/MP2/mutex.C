#include "mutex.H"
#include <cassert>

Mutex::Mutex() {
	assert(pthread_mutex_init(&m, NULL) == 0);
}

Mutex::~Mutex() {
	assert(pthread_mutex_destroy(&m) == 0);
}

void Mutex::Lock() {
	pthread_mutex_lock(&m);
}

void Mutex::Unlock() {
	pthread_mutex_unlock(&m);
}
