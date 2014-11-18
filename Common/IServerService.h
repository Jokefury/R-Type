
#ifndef __ISERVERSERVICE_H__
#define __ISERVERSERVICE_H__

#include "IService.h"

class IServerService
{
public:
	virtual ~IServerService() {}
	virtual IService* acceptService() = 0;
	virtual void closeService() = 0;
	virtual void const* getRealType() const = 0;
	virtual bool listenServer() = 0;
	virtual void wait() = 0;
};

#else

class IServerService;

#endif