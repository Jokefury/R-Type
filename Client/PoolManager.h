
#pragma once

#include <queue>

template<typename T>
class PoolManager
{
private:
  int poolInc_;
  std::queue<T*> queue_;

public:
  PoolManager(int poolSize = 10, int poolInc = 5)
    : poolInc_(poolInc)
  {
    for (; poolSize; --poolSize)
      {
	this->queue_.push(new T);
      }
  }
  ~PoolManager()
  {
    while (!this->queue_.empty())
      {
	delete this->queue_.front();
	this->queue_.pop();
      }
  }

  unsigned int size() const
  {
    return this->queue_.size();
  }
  
  void pushItem(T* item)
  {
    this->queue_.push(item);
  }

  T* getItem()
  {
    if (this->queue_.empty())
      for (int i = 0; i < this->poolInc_; ++i)
	this->queue_.push(new T);
    T* tmp = this->queue_.front();
    this->queue_.pop();
    return tmp;
  }
};
