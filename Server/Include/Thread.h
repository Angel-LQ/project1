#ifndef _THREAD_
#define _THREAD_

#include "Noncopyable.h"
#include <pthread.h>

class Thread:private Noncopyable
{
public:
	Thread();
	~Thread();

	void start();
	void join();
private:
	virtual void run()=0;
	static void* threadFunc(void*);
	pthread_t _pthId;
	bool _isRunning;
};

#endif
