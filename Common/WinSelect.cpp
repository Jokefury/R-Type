
#include "WinSelect.h"

Select::Select()
  : max_(0)
{
  WSAStartup(MAKEWORD(2, 2), &this->wsaData_);
  FD_ZERO(&this->rdfs_);
  FD_ZERO(&this->wrfs_);
  this->timeout_.tv_sec = -1;
  this->timeout_.tv_usec = -1;
}

Select::~Select()
{
  WSACleanup();
}

bool Select::canRead(unsigned int id)
{
  return (FD_ISSET(*this->sockets_[id], &this->rdfs_) != 0);
}

bool Select::canWrite(unsigned int id)
{
  return (FD_ISSET(*this->sockets_[id], &this->wrfs_) != 0);
}

void Select::initSocket(IService const* sock, bool read, bool write)
{
  if (!sock)
    return ;
  if (!read && !write && this->sockets_.find(sock->getId()) != this->sockets_.end())
    {
      SOCKET const* tmp = this->sockets_[sock->getId()];
      if (this->max_ == *this->sockets_[sock->getId()])
        {
	  this->sockets_.erase(sock->getId());	  
          this->max_ = 0;
          for (std::map<unsigned int, SOCKET const*>::const_iterator it = this->sockets_.begin(); it != this->sockets_.end(); ++it)
            {
              if (*it->second > this->max_)
                this->max_ = *it->second;
            }
        }
      FD_CLR(*tmp, &this->rdfs_);
      FD_CLR(*tmp, &this->wrfs_);
    }
  else
    {
      this->sockets_[sock->getId()] = reinterpret_cast<SOCKET const*>(sock->getRealType());
      if (*this->sockets_[sock->getId()] > this->max_)
        this->max_ = *this->sockets_[sock->getId()];
      if (read)
        FD_SET(*this->sockets_[sock->getId()], &this->rdfs_);
      else
        FD_CLR(*this->sockets_[sock->getId()], &this->rdfs_);
      if (write)
        FD_SET(*this->sockets_[sock->getId()], &this->wrfs_);
      else
        FD_CLR(*this->sockets_[sock->getId()], &this->wrfs_);
    }
}

void Select::initSocket(IServerService const* sock, bool read)
{
  if (!sock)
    return ;
  if (!read && this->sockets_.find(0) != this->sockets_.end())
    {
      SOCKET const* tmp = this->sockets_[0];
      if (this->max_ == *this->sockets_[0])
        {
	  this->sockets_.erase(0);
          this->max_ = 0;
          for (std::map<unsigned int, SOCKET const*>::const_iterator it = this->sockets_.begin(); it != this->sockets_.end(); ++it)
            {
              if (*it->second > this->max_)
                this->max_ = *it->second;
            }
        }
      FD_CLR(*tmp, &this->rdfs_);
    }
  else
    {
      this->sockets_[0] = reinterpret_cast<SOCKET const*>(sock->getRealType());
      if (*this->sockets_[0] > this->max_)
        this->max_ = *this->sockets_[0];
      if (read)
        FD_SET(*this->sockets_[0], &this->rdfs_);
      else
        FD_CLR(*this->sockets_[0], &this->rdfs_);
    }
}

bool Select::selectSocket()
{
  timeval* time = &this->timeout_;

  if (this->timeout_.tv_sec == -1 && this->timeout_.tv_usec == -1)
    time = 0;
  if (select(this->max_ + 1, &this->rdfs_, &this->wrfs_, 0, time) < 0)
    return false;
  return true;
}

void Select::setTimeout(unsigned int millisec)
{
  if (millisec == Select::NO_TIMEOUT)
    {
      this->timeout_.tv_sec = -1;
      this->timeout_.tv_usec = -1;
    }
  else
    {
      this->timeout_.tv_sec = millisec / 1000;
      this->timeout_.tv_usec = (millisec % 1000) * 1000;
    }
}
