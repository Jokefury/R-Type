#include "Worker.h"

Worker::Worker(SafeBool* b, ICondVar* notifier, SafeQueue<ITask*>& tasks)
	: b_(b), notifier_(notifier), tasks_(tasks)
{
}

void Worker::operator()()
{
  while (true)
    {
      ITask* task;
      this->b_->setBool(false);
      this->notifier_->sleepCondVar();
      if (this->tasks_.tryPop(task))
	{
	  this->b_->setBool(true);
	  (*task)();
	  delete task;
	}
     }
}
