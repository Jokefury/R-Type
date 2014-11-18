
#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t pullSize)
  : notifier_(new CondVar()), tasks_(), pullSize_(pullSize) 
{
  for (unsigned int i = 0; i < this->pullSize_; ++i)
    {
      std::pair<IThread*, SafeBool*> current = std::make_pair<IThread*, SafeBool*>(0, new SafeBool(false, new Mutex()));
      current.first = new Thread<Worker>(new Worker(current.second, this->notifier_, this->tasks_));
      this->workers_.push_back(current);
    }
}

void	ThreadPool::pushTask(ITask * task)
{
  this->tasks_.push(task);
}

void	ThreadPool::addWorker()
{
  if (this->getNbWorking() == this->getNbWorker())
    {
      for (unsigned int i = 0; i < this->pullSize_; ++i)
	{
	  std::pair<IThread*, SafeBool*> current = std::make_pair<IThread*, SafeBool*>(0, new SafeBool(false, new Mutex()));
	  current.first = new Thread<Worker>(new Worker(current.second, this->notifier_, this->tasks_));
	  this->workers_.push_back(current);
	}
    }
  this->notifier_->wakeCondVar();
}

size_t	ThreadPool::getNbWorker() const
{
  return this->workers_.size();
}

size_t	ThreadPool::getNbWorking()
{
  size_t nb = 0;

  std::list< std::pair<IThread*, SafeBool*> >::iterator it = this->workers_.begin();
  for (; it != this->workers_.end(); ++it)
    {
      if (it->second->getBool())
	++nb;
    }
  return nb;
}

size_t	ThreadPool::getNbTask() const
{
  return this->tasks_.size();
}
