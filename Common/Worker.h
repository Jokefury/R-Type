#pragma once

#include "ICondVar.h"
#include "SafeBool.h"
#include "ITask.h"
#include "SafeQueue.h"
#include "IThread.h"
#include <list>

class Worker
{
	SafeBool*			b_;
	ICondVar*			notifier_;
	SafeQueue<ITask*>&	tasks_;

public : 
	Worker(SafeBool* b, ICondVar* notifier, SafeQueue<ITask*>& tasks);
	~Worker() {}
	void operator()();
};
