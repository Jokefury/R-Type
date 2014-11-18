
#include "UnixTCPService.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
** Id 0 refer to a ServerService
*/
unsigned int TCPService::lastId = 1;

TCPService::TCPService()
  : id_(TCPService::lastId++), sock_(-1)
{
  this->buffer_ = new char[BUFF_SIZE];
}

TCPService::TCPService(int csock, std::string const& host)
  : id_(TCPService::lastId++), host_(host), sock_(csock)
{
  this->buffer_ = new char[BUFF_SIZE];
}

TCPService::~TCPService()
{
  delete[] this->buffer_;
  if (this->sock_ != -1)
    this->closeService();
  while (!this->send_.empty())
    {
      delete this->send_.front();
      this->send_.pop();
    }
  while (!this->recv_.empty())
    {
      delete this->recv_.front();
      this->recv_.pop();
    }
}

bool TCPService::closeService()
{
  if (!close(this->sock_))
    {
      this->sock_ = -1;
      return true;
    }
  return false;
}

bool TCPService::connectTo(std::string const& name, int port)
{
  struct sockaddr_in sin;

  if ((this->sock_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return false;
  int option = 1;
  if (setsockopt(this->sock_, SOL_SOCKET, SO_REUSEADDR,
		 reinterpret_cast<char*>(&option), sizeof(option)) == -1)
    return false;
  sin.sin_addr.s_addr = inet_addr(name.c_str());
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if(connect(this->sock_, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      this->closeService();
      return false;
    }
  return true;
}

unsigned int TCPService::getId() const
{
  return this->id_;
}

std::string const& TCPService::getHost() const
{
	return this->host_;
}

void const* TCPService::getRealType() const
{
  if (this->sock_ == -1)
    return 0;
  return &this->sock_;
}

DataPacket const* TCPService::getPacket()
{
  DataPacket* ret = 0;

  if (!this->recv_.empty() && this->recv_.front()->data.size() == *reinterpret_cast<unsigned short const*>(this->recv_.front()->data.c_str()))
    {
      ret = this->recv_.front();
      this->recv_.pop();
    }
  return ret;
}

void TCPService::pushPacket(DataPacket* packet)
{
  this->send_.push(packet);
}

bool TCPService::flushRecv()
{
  DataPacket* ret;
  int n;
  int tmp = 0;

  if ((n = recv(this->sock_, this->buffer_, BUFF_SIZE, MSG_NOSIGNAL)) <= 0)
     return false;
   if (!this->recv_.empty() && this->recv_.back()->data.size() < *reinterpret_cast<unsigned short const*>(this->recv_.back()->data.c_str()))
    {
      tmp = *reinterpret_cast<unsigned short const*>(this->recv_.back()->data.c_str()) - this->recv_.back()->data.size();
      if (tmp > n)
	tmp = n;
      this->recv_.back()->data.append(this->buffer_, tmp);
    }
   for (int i = tmp; i < n;)
    {
      ret = new DataPacket;
      tmp = *reinterpret_cast<unsigned short*>(&this->buffer_[i]);
      if ((tmp + i) > n)
	tmp = n - i;
      ret->data.assign(&this->buffer_[i], tmp);
      this->recv_.push(ret);
      i += tmp;
    }
  return true;
}

void TCPService::flushSend()
{
  int ret;

  while (!this->send_.empty())
    {
      if ((ret = send(this->sock_, this->send_.front()->data.c_str(), this->send_.front()->data.size(), MSG_NOSIGNAL)) == -1)
	return ;
      if (static_cast<unsigned int>(ret) < this->send_.front()->data.size())
	this->send_.front()->data.erase(0, ret);
      else
	{
	  delete this->send_.front();
	  this->send_.pop();
	}
    }
}
