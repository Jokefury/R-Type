
#ifndef __UNIX_THREAD_H__
#define __UNIX_THREAD_H__

#include <pthread.h>
#include "IThread.h"
#include <csignal>

template<typename T>
class Thread : public IThread
{
private:
  pthread_t thread_;
  int id_;
  T* routine_;

private:
  static void* run(void *args)
  {
	Thread const* This = reinterpret_cast<Thread const*>(args);
	(*(This->routine_))();
	return 0;
  }

public:
  Thread(T *routine) : routine_(routine)
  {
	this->id_ = pthread_create(&this->thread_, 0, &Thread::run, this);
  }

  virtual ~Thread()
  {
    delete this->routine_;
  }

  virtual void stop()
  {
	pthread_kill(this->thread_, SIGTERM);
  }

  virtual void wait()
  {
	pthread_join(this->thread_, 0);
  }
};

#else

template<typename T>
class Thread;

#endif
