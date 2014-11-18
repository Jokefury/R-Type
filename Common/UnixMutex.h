
#ifndef __UNIX_MUTEX_H__
#define __UNIX_MUTEX_H__

#include <pthread.h>
#include "IMutex.h"

class Mutex : public IMutex
{
private:
	pthread_mutex_t _m;

public:
	Mutex();
	virtual ~Mutex();
	virtual void lock();
	virtual void unlock();
	virtual bool tryLock();
};

#else

class Mutex;

#endif
