
#ifndef __ISERVICE_H__
#define __ISERVICE_H__

#include "Packman.h"
#include <string>

class IService
{
public:
	virtual ~IService() {}
	virtual bool closeService() = 0;
	virtual bool connectTo(std::string const& name, int port) = 0;
	virtual unsigned int getId() const = 0;
	virtual std::string const& getHost() const = 0;
	virtual void const* getRealType() const = 0;
	virtual DataPacket const* getPacket() = 0;
	virtual void pushPacket(DataPacket* packet) = 0;
	virtual bool flushRecv() = 0;
	virtual void flushSend() = 0;
};

#else

class IService;

#endif
