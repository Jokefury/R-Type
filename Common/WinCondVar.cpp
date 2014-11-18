
#include "WinCondVar.h"

CondVar::CondVar()
{
	InitializeConditionVariable(&this->_cond);
	InitializeCriticalSection(&this->_m);
}

CondVar::~CondVar()
{
	DeleteCriticalSection(&this->_m);
}

void CondVar::sleepCondVar()
{
	EnterCriticalSection (&_m);
	SleepConditionVariableCS(&this->_cond, &this->_m, INFINITE);
	LeaveCriticalSection(&this->_m);
}

void CondVar::wakeCondVar()
{
	WakeConditionVariable(&this->_cond);
}
