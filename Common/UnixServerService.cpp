
#include "UnixServerService.h"
#include "UnixTCPService.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

ServerService::ServerService(int port)
  : sock_(-1), port_(port)
{
}

ServerService::~ServerService()
{
}

IService* ServerService::acceptService()
{
  int csock;
  struct sockaddr_in csin;
  socklen_t len = sizeof(csin);
  
  csock = accept(this->sock_, (struct sockaddr*)&csin, &len);

  if (csock == -1)
    return 0;
  return new TCPService(csock, inet_ntoa(csin.sin_addr));
}

void ServerService::closeService()
{
  close(this->sock_);
  this->sock_ = -1;
}

void const* ServerService::getRealType() const
{
  if (this->sock_ == -1)
    return 0;
  return &this->sock_;
}

bool ServerService::listenServer()
{
  if ((this->sock_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return false;
  int option = 1;
  if (setsockopt(this->sock_, SOL_SOCKET, SO_REUSEADDR,
		 reinterpret_cast<char*>(&option), sizeof(option)) == -1)
    return false;
  struct sockaddr_in sin;

  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(this->port_);
  sin.sin_family = AF_INET;
  if(bind(this->sock_, (struct sockaddr*) &sin, sizeof(sin)) == -1)
    {
      this->closeService();
      return false;
    }
  if(listen(this->sock_, 5) == -1)
    {
      this->closeService();
      return false;
    }
  return true;
}

void ServerService::wait()
{
}
