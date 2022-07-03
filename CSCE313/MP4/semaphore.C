#include "semaphore.H"

Semaphore::Semaphore(int _value) {
	value = _value;
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&c, NULL);
}

Semaphore::~Semaphore() {
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
}

int Semaphore::P() {
	// decrement & block if negative
	pthread_mutex_lock(&m);
	value--;
	if (value < 0) {
		pthread_cond_wait(&c, &m);
	}
	pthread_mutex_unlock(&m);
	return 0;
}

int Semaphore::V() {
	// increment & unblock if non-positive
	pthread_mutex_lock(&m);
	value++;
	if (value <= 0) {
		pthread_cond_signal(&c);
	}
	pthread_mutex_unlock(&m);
	return 0;
}
