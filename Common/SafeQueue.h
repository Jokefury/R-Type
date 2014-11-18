#pragma once

#include <queue>

#include "ScopedLock.h"

#if defined(_WIN32) || defined(_WIN64)
#include "WinMutex.h"
#include "WinCondVar.h"
#elif UNIX
#include "UnixMutex.h"
#include "UnixCondVar.h"
#endif

template<class T>
class SafeQueue
{
private :
  std::queue<T>	queue_;
  ICondVar*	cond_;
  IMutex*	mutex_;

public :

  SafeQueue(bool blocking = false)
    : cond_(0), mutex_(0)
  {
    if (blocking)
      this->cond_ = new CondVar;
    this->mutex_ = new Mutex;
  }

  ~SafeQueue()
  {
    delete this->mutex_;
  }

  T front()
  {
    ScopedLock	sl(this->mutex_);

    return this->queue_.front();
  }

  bool tryPop(T &ret)
  {
    ScopedLock	sl(this->mutex_);

    if (!this->queue_.empty())
      {
	ret = this->queue_.front();
	this->queue_.pop();
	return true;
      }
    if (this->cond_)
      this->cond_->sleepCondVar();
    return false;
  }

  bool empty()
  {
    ScopedLock	sl(this->mutex_);

    return this->queue_.empty();
  }

  void push(T elem)
  {
    ScopedLock	sl(this->mutex_);
    
    if (this->cond_ && this->queue_.empty())
      this->cond_->wakeCondVar();
    this->queue_.push(elem);
  }

  size_t	size() const
  {
    ScopedLock	sl(this->mutex_);
    return this->queue_.size();
  }
};
