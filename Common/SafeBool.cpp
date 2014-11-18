#include "ScopedLock.h"
#include "SafeBool.h"

SafeBool::SafeBool(bool b, IMutex* mutex)
	: b_(b), mutex_(mutex)
{
}

void SafeBool::setBool(bool b)
{
  ScopedLock sl(this->mutex_);
  this->b_ = b;
}

bool SafeBool::getBool()
{
  ScopedLock sl(this->mutex_);
  bool b = this->b_;
  return b;
}
