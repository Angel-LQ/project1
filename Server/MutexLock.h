#ifndef _MUTEXLOCK_
#define _MUTEXLOCK_

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock:private Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	pthread_mutex_t* getMutexPtr();
private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};

class MutexLockGuard:private Noncopyable
{
public:
	MutexLockGuard(MutexLock &mutexLock);
	~MutexLockGuard();
private:
	MutexLock & _mutexLock;
};

#endif
