
#include "UnixCondVar.h"

CondVar::CondVar()
{
  pthread_mutex_init(&this->_m, NULL);
  pthread_cond_init(&this->_cond, 0);
}

CondVar::~CondVar()
{
}

void CondVar::sleepCondVar()
{
  pthread_mutex_lock(&this->_m);
  pthread_cond_wait(&this->_cond, &this->_m);
  pthread_mutex_unlock(&this->_m);
}

void CondVar::wakeCondVar()
{
  pthread_cond_broadcast(&this->_cond);
}
