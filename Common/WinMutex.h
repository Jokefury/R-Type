
#ifndef __WIN_MUTEX_H__
#define __WIN_MUTEX_H__

#include "IMutex.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class Mutex : public IMutex
{
private:
	CRITICAL_SECTION _m;

public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
	bool tryLock();
};

#else

class Mutex;

#endif
