
#ifndef __WIN_SERVER_SERVICE_H__
#define __WIN_SERVER_SERVICE_H__

#include "IServerService.h"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

class ServerService : public IServerService
{
private:
	WSADATA wsaData_;
	SOCKET sock_;
	int port_;

public:
	ServerService(int port);
	virtual ~ServerService();
	virtual IService* acceptService();
	virtual void closeService();
	virtual void const* getRealType() const;
	virtual bool listenServer();
	virtual void wait();
};

#else

class ServerService;

#endif