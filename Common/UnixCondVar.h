
#ifndef __UNIX_CONDVAR_H__
#define __UNIX_CONDVAR_H__

#include <pthread.h>
#include "ICondVar.h"

class CondVar : public ICondVar
{
private:
  pthread_cond_t _cond;
  pthread_mutex_t _m;

public:
  CondVar();
  virtual ~CondVar();
  virtual void sleepCondVar();
  virtual void wakeCondVar();
};

#else

class CondVar;

#endif
