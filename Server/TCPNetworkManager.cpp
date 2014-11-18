
#include "InitializeError.h"
#include "TCPNetworkManager.h"

TCPNetworkManager::TCPNetworkManager(int port)
  : select_(new Select), acceptor_(new ServerService(port))
{
  if (!this->acceptor_->listenServer())
      throw InitializeError ("Cannot listen");
  this->select_->initSocket(this->acceptor_, true);
  this->select_->setTimeout(Select::NO_TIMEOUT);
}

TCPNetworkManager::~TCPNetworkManager()
{
  for (std::map<int, IService*>::iterator it = this->clients_.begin(); it != this->clients_.end(); ++it)
    {
      it->second->closeService();
      delete it->second;
    }
  this->clients_.clear();
  this->acceptor_->closeService();
  delete this->acceptor_;
  delete this->select_;
}

IService* TCPNetworkManager::acceptService()
{
  if (this->select_->canRead(0))
    {
      IService *s;
      if ((s = this->acceptor_->acceptService()) != 0)
        {
          this->select_->initSocket(this->acceptor_, true);
          return s;
        }
    }
  this->select_->initSocket(this->acceptor_, true);
  return 0;
}

void TCPNetworkManager::addService(IService *client)
{
  this->clients_[client->getId()] = client;
  this->select_->initSocket(client, true, false);
}

void TCPNetworkManager::deleteService(int id)
{
  if (this->clients_.find(id) != this->clients_.end())
    {
      this->select_->initSocket(this->clients_[id], false, false);
      this->clients_[id]->closeService();
      delete this->clients_[id];
      this->clients_.erase(id);
    }
}

bool TCPNetworkManager::recvFromService(int id, DataPacket const ** ret)
{
  std::map<int, IService*>::iterator it;

  if ((it = this->clients_.find(id)) != this->clients_.end())
    {

      if (this->select_->canRead(it->second->getId()))
        if (!it->second->flushRecv())
			return false;
      this->select_->initSocket(it->second, true, false);
      *ret = it->second->getPacket ();
	  return true;
    }
  *ret = 0;
  return true;
}

void TCPNetworkManager::sendToService(int id, DataPacket * pckt)
{
  std::map<int, IService*>::iterator it;

  if ((it = this->clients_.find(id)) != this->clients_.end())
    {
      it->second->pushPacket(pckt);
      it->second->flushSend();
    }
}

void TCPNetworkManager::wait(unsigned int time)
{
  this->select_->setTimeout(time);
  this->select_->selectSocket();
}
