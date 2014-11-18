#include        "Room.h"

short     Room::port_ = 4242;

Room::Room(int id, int config, std::list<int> & ready) :
  id_ (id), running_ (false), config_ (config), nbReady_ (0), ready_ (ready), ports_ (Room::port_, Room::port_ + 1)
{
  port_ += 2;
}

Room::~Room()
{
}

const std::list<const User*>&  Room::getClients() const
{
  return clients_;
}

bool    Room::pushClient(const User * u)
{
  if (clients_.size () == 4)
    return false;
  clients_.push_back (u);
  return true;
}

bool    Room::popClient(const User * u)
{
  std::list<const User*>::iterator       it;

  for (it = clients_.begin (); it != clients_.end (); ++it)
    if ((*it)->id_ == u->id_)
      {
        if (u->ready_)
          --nbReady_;
        clients_.erase (it);
	if (nbReady_ == clients_.size() && nbReady_)
	  ready_.push_back(id_);
        return true;
      }
  return false;
}

bool    Room::setRunning()
{
  nbReady_ = 0;
  running_ = !running_;
  return running_;
}

bool    Room::isRunning() const
{
  return running_;
}

int     Room::getId() const
{
  return id_;
}

int     Room::getNbPlayers() const
{
  return clients_.size ();
}

void    Room::newPlayerReady()
{
  ++nbReady_;
  if (nbReady_ == clients_.size ())
    ready_.push_back (id_);
}

short     Room::getSendPort() const
{
  return ports_.first;
}

short     Room::getReceivePort() const
{
  return ports_.second;
}

int	Room::getNbReady() const 
{
  return nbReady_;
}
