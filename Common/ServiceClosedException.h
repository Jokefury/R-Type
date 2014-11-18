
#pragma once

#include <iostream>
#include <exception>

class ServiceClosedException : public std::exception
{
public:
	ServiceClosedException() throw() {}
	virtual ~ServiceClosedException() throw() {}
	virtual const char* what() const throw()
	{
		return "Service has been closed unexpectedly";
	}
};