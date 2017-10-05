#include "mutex_guard.h"

MutexGuard::MutexGuard(Mutex & m_new) {
	m = &m_new;
	m->Lock();
}

MutexGuard::~MutexGuard() {
	m->Unlock();
}
