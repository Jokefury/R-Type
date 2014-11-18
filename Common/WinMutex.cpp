
#include "WinMutex.h"

Mutex::Mutex()
{
	InitializeCriticalSection(&this->_m);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&this->_m);
}

void Mutex::lock()
{
	EnterCriticalSection(&this->_m);
}

void Mutex::unlock()
{
	LeaveCriticalSection(&this->_m);
}

bool Mutex::tryLock()
{
	if (TryEnterCriticalSection(&this->_m))
		return true;
	return false;
}