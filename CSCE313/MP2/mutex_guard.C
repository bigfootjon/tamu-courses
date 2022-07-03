#include "mutex_guard.H"

MutexGuard::MutexGuard(Mutex & m_new) {
	m = &m_new;
	m->Lock();
}

MutexGuard::~MutexGuard() {
	m->Unlock();
}
