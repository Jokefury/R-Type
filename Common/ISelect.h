
#ifndef __ISELECT_H__
#define __ISELECT_H__

#include "IService.h"
#include "IServerService.h"

class ISelect
{
public:
	virtual ~ISelect() {}
	virtual bool canRead(unsigned int id) = 0;
	virtual bool canWrite(unsigned int id) = 0;
	virtual void initSocket(IService const* sock, bool read, bool write) = 0;
	virtual void initSocket(IServerService const* sock, bool read) = 0;
	virtual bool selectSocket() = 0;
	virtual void setTimeout(unsigned int millisec) = 0;
};

#else

class ISelect;

#endif
