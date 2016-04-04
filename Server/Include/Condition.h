#ifndef _CONDITION_
#define _CONDITION_

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;

class Condition:private Noncopyable
{
public:
	Condition(MutexLock &mutexLock);
	~Condition();

	void wait();
	void notify();
	void notifyAll();
private:
	pthread_cond_t _cond;
	MutexLock &_mutexLock;
};

#endif
