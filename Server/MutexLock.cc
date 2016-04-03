#include "MutexLock.h"
#include <iostream>

MutexLock::MutexLock()
: _isLocking(false)
{
	pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}

pthread_mutex_t * MutexLock::getMutexPtr()
{
	return &_mutex;
}

MutexLockGuard::MutexLockGuard(MutexLock &mutexLock)
:_mutexLock(mutexLock)
{
	_mutexLock.lock();	
}

MutexLockGuard::~MutexLockGuard()
{
	_mutexLock.unlock();
}
