
#include "UnixMutex.h"

Mutex::Mutex()
{
  pthread_mutex_init(&this->_m,NULL);
}

Mutex::~Mutex()
{
}

void Mutex::lock()
{
  pthread_mutex_lock(&this->_m);
}

void Mutex::unlock()
{
  pthread_mutex_unlock(&this->_m);
}

bool Mutex::tryLock()
{
  return (pthread_mutex_trylock(&this->_m) != 0);
}
