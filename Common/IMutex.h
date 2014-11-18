
#ifndef __IMUTEX_H__
#define __IMUTEX_H__

class IMutex
{
public:
	virtual ~IMutex() {}
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual bool tryLock() = 0;
};

#else

class IMutex;

#endif
