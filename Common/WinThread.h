
#ifndef __WIN_THREAD_H__
#define __WIN_THREAD_H__

#include "IThread.h"
#include <windows.h>

template<typename T>
class Thread : public IThread
{
private:
	HANDLE thread_;
	DWORD id_;
	T* routine_;

private:
	static void run(void *args)
	{
	  Thread const* This = reinterpret_cast<Thread const*>(args);
	  (*This->routine_)();
	}

public:
	Thread(T* routine) : routine_(routine)
	{
	  this->thread_ = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Thread::run), this, 0, &this->id_);
	}

	virtual ~Thread() {}
	virtual void stop()
	{
	  TerminateThread(this->thread_, 0);
	}

	virtual void wait()
	{
	  WaitForSingleObject(this->thread_, 0);
	}
};

#else

template<typename T>
class Thread;

#endif
