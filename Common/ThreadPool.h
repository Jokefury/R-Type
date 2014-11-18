#pragma once

#include <list>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64)

#include "WinCondVar.h"
#include "WinMutex.h"
#include "WinThread.h"

#elif UNIX

#include "UnixCondVar.h"
#include "UnixMutex.h"
#include "UnixThread.h"

#endif

#include "ITask.h"
#include "SafeBool.h"
#include "SafeQueue.h"
#include "Worker.h"

class ThreadPool
{
  ICondVar*		notifier_;
  SafeQueue< ITask* >	tasks_;
  size_t		pullSize_;
  std::list< std::pair<IThread*, SafeBool*> >		workers_;

public :

  ThreadPool(size_t nbWorker = 10);
  void		addWorker();
  size_t	getNbWorker() const;
  size_t	getNbWorking();
  size_t	getNbTask() const;
  void          pushTask(ITask * task);
  };
