
#ifndef __UNIX_SELECT_H__
#define __UNIX_SELECT_H__

#include "ISelect.h"
#include <map>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

class Select : public ISelect
{
private:
	std::map<unsigned int, unsigned int> sockets_;
	unsigned int max_;
	struct timeval timeout_;
	fd_set rdfs_;
	fd_set wrfs_;

public:
	static const unsigned int NO_TIMEOUT = -1;

public:
	Select();
	virtual ~Select();
	virtual bool canRead(unsigned int id);
	virtual bool canWrite(unsigned int id);
	virtual void initSocket(IService const* sock, bool read, bool write);
	virtual void initSocket(IServerService const* sock, bool read);
	virtual bool selectSocket();
	virtual void setTimeout(unsigned int millisec);
};

#else

class Select;

#endif
