
#include "WinTCPService.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


/*
** Id 0 refer to a ServerService
*/
unsigned int TCPService::lastId = 1;

TCPService::TCPService()
	: id_(lastId++), sock_(INVALID_SOCKET)
{
	this->buffer_ = new char[BUFF_SIZE];
}

TCPService::TCPService(SOCKET csock, std::string const& host)
	: id_(lastId++), host_(host), sock_(csock)
{
	this->buffer_ = new char[BUFF_SIZE];
	WSAStartup(MAKEWORD(2,2), &this->wsaData_);
}

TCPService::~TCPService()
{
	delete[] this->buffer_;
	if (this->sock_ != INVALID_SOCKET)
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
	closesocket(this->sock_);
	this->sock_ = INVALID_SOCKET;
	WSACleanup();
	return true;
}

bool TCPService::connectTo(std::string const& ip, int port)
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

	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(connect(this->sock_, (SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		WSACleanup();
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
	if (this->sock_ == INVALID_SOCKET)
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

#include <iostream>

bool TCPService::flushRecv()
{
  	DataPacket* ret;
	int n;
	int tmp = 0;

	if ((n = recv(this->sock_, this->buffer_, BUFF_SIZE, 0)) == SOCKET_ERROR)
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
		if ((ret = send(this->sock_, this->send_.front()->data.c_str(), this->send_.front()->data.size(), 0)) == SOCKET_ERROR)
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
