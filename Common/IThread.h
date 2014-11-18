
#ifndef __ITHREAD_H__
#define __ITHREAD_H__

class IThread
{
public:
	virtual ~IThread() {}
	virtual void stop() = 0;
	virtual void wait() = 0;
};

#else

class IThread;

#endif