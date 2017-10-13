#include <pthread.h>
#include <time.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void usleep(unsigned long usec) {
	pthread_mutex_lock(&m);
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	now.tv_nsec += usec;
	pthread_cond_timedwait(&c, &m, &now);
}
