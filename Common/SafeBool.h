#pragma once

#include "IMutex.h"

class SafeBool
{
	bool	b_;
	IMutex*	mutex_;

public :
	SafeBool(bool b, IMutex* mutex);
	void setBool(bool b);
	bool getBool();
};