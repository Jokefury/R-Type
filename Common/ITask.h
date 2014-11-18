#pragma once

class ITask
{
	public :
		virtual void operator()() = 0;
		virtual ~ITask() {}
};