
#include <algorithm>
#include <iostream>
#include "UDPNetworkManager.h"
#include "InitializeError.h"

UDPNetworkManager::UDPNetworkManager(const std::list<const User *>& clients, int port)
  : clients_(clients)
{
  std::string ip("127.0.0.1");

  this->socket_ = new UDPService();
  if (!this->socket_->connectTo(ip, port))
    throw InitializeError("socket connection");
  this->select_ = new Select();
  this->select_->initSocket(this->socket_, true, false);
  this->select_->setTimeout(Select::NO_TIMEOUT);
}

void UDPNetworkManager::wait(int time)
{
  this->select_->setTimeout(time);
  this->select_->selectSocket();
}

bool UDPNetworkManager::recvFromService(int & id, const DataPacket ** ret)
{

  if (this->select_->canRead(this->socket_->getId()))
    if (!this->socket_->flushRecv())
      return false;
  this->select_->initSocket(this->socket_, true, false);
  if ((*ret = this->socket_->getPacket ()) == 0)
    return true;

  std::list<const User *>::const_iterator it = this->clients_.begin();
  for (; it != this->clients_.end(); ++it)
    {
      if ((*ret)->endpoint.host == (*it)->host_)
        {
          id = (*it)->id_;
        }
    }
  return true;
}

void UDPNetworkManager::sendToServices(DataPacket* pckt)
{
  std::list<const User *>::const_iterator it = this->clients_.begin();

  while (it != this->clients_.end())
    {
      pckt->endpoint.host = (*it)->host_;
      pckt->endpoint.port = (*it)->port_;
      this->socket_->pushPacket(pckt);
      ++it;
      if (it != this->clients_.end())
        pckt = new DataPacket (*pckt);
    }
  this->socket_->flushSend();
}
