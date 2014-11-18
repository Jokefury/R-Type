
#pragma once

#include "IMutex.h"

class ScopedLock
{
  IMutex* const & mutex_;

 public:
  ScopedLock(IMutex* const & m)
    : mutex_(m)
  {
    this->mutex_->lock();
  }

  ~ScopedLock()
  {
    this->mutex_->unlock();
  }
};
