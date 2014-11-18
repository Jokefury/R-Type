
#ifndef __WIN_SELECT_H__
#define __WIN_SELECT_H__

#include "ISelect.h"
#include <winsock2.h>
#include <time.h>
#include <map>

class Select : public ISelect
{
private:
	WSADATA wsaData_;
	std::map<unsigned int, SOCKET const*> sockets_;
	SOCKET max_;
	timeval timeout_;
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
