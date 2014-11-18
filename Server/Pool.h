#pragma once

#include <queue>

template <typename T>
class Pool
{
private:
  std::queue<T>        pool_;

public:
  Pool(){};
  ~Pool(){};

  T  getElement()
  {
    T  ptr;

    if (this->pool_.size() > 0)
      {
        ptr = this->pool_.front();
        this->pool_.pop();
        return (ptr);
      }
    else
      return (0);
  };

  void  pushElement(T e)
  {
    this->pool_.push(e);
  };

  int   size() const
  {
    return pool_.size ();
  }

};
