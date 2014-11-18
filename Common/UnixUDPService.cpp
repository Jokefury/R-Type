
#include "UnixUDPService.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

unsigned int UDPService::lastId = 0;

UDPService::UDPService()
  : id_(UDPService::lastId++), sock_(-1)
{
  this->buffer_ = new char[BUFF_SIZE];
}

UDPService::~UDPService()
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

bool UDPService::closeService()
{
  if (!close(this->sock_))
    {
      this->sock_ = -1;
      return true;
    }
  return false;
}

bool UDPService::connectTo(std::string const& host, int port)
{
  struct sockaddr_in sin;

  if ((this->sock_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    return false;
  int option = 1;
  if (setsockopt(this->sock_, SOL_SOCKET, SO_REUSEADDR,
		 reinterpret_cast<char*>(&option), sizeof(option)) == -1)
    return false;
  this->host_ = host;
  if (port == -1)
    return true;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if(bind(this->sock_, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) == -1)
    {
      this->closeService();
      return false;
    }
  return true;
}

unsigned int UDPService::getId() const
{
  return this->id_;
}

std::string const& UDPService::getHost() const
{
	return this->host_;
}

void const* UDPService::getRealType() const
{
  if (this->sock_ == -1)
    return 0;
  return &this->sock_;
}

DataPacket const* UDPService::getPacket()
{
  DataPacket* ret = 0;

  if (!this->recv_.empty() && this->recv_.front()->data.size() == *reinterpret_cast<unsigned short const*>(this->recv_.front()->data.c_str()))
    {
      ret = this->recv_.front();
      this->recv_.pop();
    }
  return ret;
}

void UDPService::pushPacket(DataPacket* packet)
{
  this->send_.push(packet);
}

#include <iostream>

bool UDPService::flushRecv()
{
  struct sockaddr_in in;
  socklen_t inSize = sizeof(in);
  DataPacket* ret;
  int n;
  int tmp = 0;

  if ((n = recvfrom(this->sock_, this->buffer_, BUFF_SIZE,
                    0, reinterpret_cast<struct sockaddr*>(&in), &inSize)) <= 0)
    return false;
  if (!this->recv_.empty() && this->recv_.back()->data.size()
      < *reinterpret_cast<unsigned short const*>(this->recv_.back()->data.c_str()))
    {
      tmp = *reinterpret_cast<unsigned short const*>(this->recv_.back()->data.c_str())
        - this->recv_.back()->data.size();
      if (tmp > n)
        tmp = n;
      this->recv_.back()->data.append(this->buffer_, tmp);
    }
  for (int i = tmp; i < n;)
    {
      ret = new DataPacket;
      ret->endpoint.host = inet_ntoa(in.sin_addr);
      ret->endpoint.port = ntohs(in.sin_port);
      tmp = *reinterpret_cast<unsigned short*>(&this->buffer_[i]);
      if ((tmp + i) > n)
        tmp = n - i;
      ret->data.assign(&this->buffer_[i], tmp);
      this->recv_.push(ret);
      i += tmp;
    }
  return true;
}

void UDPService::flushSend()
{
  struct sockaddr_in to;
  int toSize = sizeof(to);
  int ret;

  to.sin_family = AF_INET;
  while (!this->send_.empty())
    {
      to.sin_addr.s_addr = inet_addr(this->send_.front()->endpoint.host.c_str());
      to.sin_port = htons(this->send_.front()->endpoint.port);
      if ((ret = sendto(this->sock_, this->send_.front()->data.c_str(),
                        this->send_.front()->data.size(), 0,
                        reinterpret_cast<struct sockaddr*>(&to), toSize)) == -1)
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
