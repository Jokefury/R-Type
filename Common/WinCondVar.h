
#ifndef __WIN_CONDVAR_H__
#define __WIN_CONDVAR_H__

#include <windows.h>
#include "ICondVar.h"

class CondVar : public ICondVar
{
private:
	CONDITION_VARIABLE _cond;
	CRITICAL_SECTION _m;

public:
	CondVar();
	virtual ~CondVar();
	virtual void sleepCondVar();
	virtual void wakeCondVar();
};

#else

class CondVar;

#endif
