
#include "WinServerService.h"
#include "WinTCPService.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

ServerService::ServerService(int port)
  : port_(port), sock_(INVALID_SOCKET)
{
}

ServerService::~ServerService()
{
}

IService* ServerService::acceptService()
{
	SOCKET csock;
	SOCKADDR_IN csin;
	int sinsize = sizeof csin;

	csock = accept(this->sock_, (SOCKADDR *)&csin, &sinsize);
	if (csock == INVALID_SOCKET)
		return 0;
	return new TCPService(csock, inet_ntoa(csin.sin_addr));
}

void ServerService::closeService()
{
	closesocket(this->sock_);
	this->sock_ = INVALID_SOCKET;
	WSACleanup();
}

void const* ServerService::getRealType() const
{
	if (this->sock_ == INVALID_SOCKET)
		return 0;
	return &this->sock_;
}

bool ServerService::listenServer()
{
	if (WSAStartup(MAKEWORD(2,2), &this->wsaData_))
		return false;
	if ((this->sock_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}
	int option = 1;
	if (setsockopt(this->sock_, SOL_SOCKET, SO_REUSEADDR,
		       reinterpret_cast<char*>(&option), sizeof(option)) == SOCKET_ERROR)
	  return false;
	SOCKADDR_IN sin;

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(this->port_);
	sin.sin_family = AF_INET;
	if(bind(this->sock_, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		WSACleanup();
		return false;
	}
	if(listen(this->sock_, 5) == SOCKET_ERROR)
	{
		WSACleanup();
		return false;
	}
	return true;
}

void ServerService::wait()
{
}
