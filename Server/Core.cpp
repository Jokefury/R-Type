
#include        <iostream>
#include        "Core.h"
#include        "RoomRequestManager.h"
#include        "AEntity.h"
#include	<csignal>

static bool gRunning = true;

static void signalHandler(int signum)
{
  std::cout << std::endl;
  if (signum == SIGINT)
    gRunning = false;
}

Core::Core() :
  nm_ (4210), rm_ (0), maxRoomId (0)
{
	rm_ = new RoomRequestManager (*this);
	AEntity::initCosSinMap();
}

Core::~Core()
{
}

void    Core::run()
{
  const DataPacket *    pckt;
  IService*     s;
  std::map<int, User>::iterator it;
  std::list<int>::iterator      it1;

  signal(SIGINT, &signalHandler);
  while (gRunning)
    {
      nm_.wait (Select::NO_TIMEOUT);
      if (!gRunning)
	break ;

      int rid;

      while (this->dones_.tryPop(rid))
      {
	for (it = this->users_.begin(); it != this->users_.end(); ++it)
	  if (it->second.curentRoom_ == rid)
	    {
	      it->second.curentRoom_ = -1;
	      it->second.ready_ = false;
	    }
	if (this->rooms_.find(rid) != this->rooms_.end())
	  this->rooms_.erase(rid);
	this->ready_.remove(rid);
      }

      for (it = users_.begin (); it != users_.end ();)
        {
          if (this->nm_.recvFromService (it->first, &pckt))
	    {
	      if (pckt)
		rm_->treatment (it->first, pckt);
	      ++it;
	    }
	  else
	    {
	      if (it->second.curentRoom_ != -1)
		this->removeUserFromRoom(it->second.id_, it->second.curentRoom_);
	      this->nm_.deleteService(it->second.id_);
	      std::map<int, User>::iterator itmp;
	      itmp = it;
	      ++it;
	      users_.erase(itmp);
	    }
        }

      createGames ();

      if ((s = nm_.acceptService ()))
        {
          createUser (s);
          nm_.addService (s);
        }
    }
}

void    Core::createUser(IService * s)
{
  std::map<int, User>::iterator it;

  if ((it = users_.find (s->getId ())) != users_.end ())
    return;
  users_.insert (std::make_pair (s->getId (), User (s->getId (), s->getHost ())));
}

void    Core::roomNotifyPlayer(Room & r, int userId, char state, const std::string& userName)
{
  const std::list<const User *>&     u = r.getClients ();
  std::list<const User *>::const_iterator       it;

  for (it = u.begin (); it != u.end (); ++it)
    {
      nm_.sendToService ((*it)->id_, rm_->treatmentRoomNotifyPlayer (state, userName));
      if (!state && (*it)->id_ != userId)
        nm_.sendToService (userId, rm_->treatmentRoomNotifyPlayer (state, (*it)->name_));
    }
}

void    Core::addUserInRoom(int userId, int roomId, std::string const& name)
{
  std::map<int, Room>::iterator it_r;
  std::map<int, User>::iterator it_u;
  std::list<const User*>::const_iterator	it;

  it_r = rooms_.find (roomId);
  it_u = users_.find (userId);
  if (it_r != rooms_.end () && it_u != users_.end () && !(it_r->second).isRunning () && (it_u->second).curentRoom_ == -1 && (it_r->second).pushClient(&it_u->second))
    {
      (it_u->second).curentRoom_ = roomId;
      (it_u->second).name_ = name;
      (it_u->second).port_ = (it_r->second).getSendPort ();
      nm_.sendToService (userId, rm_->treatmentRoomNotifyJoin (roomId, (it_u->second).port_, (it_r->second).getReceivePort (), 0));
      roomNotifyPlayer(it_r->second, userId, 0, name);
      for (it = (it_r->second).getClients ().begin (); it != (it_r->second).getClients ().end (); ++it)
	nm_.sendToService ((*it)->id_, rm_->treatmentRoomNotifyReady ((it_r->second).getNbReady ()));
    }
}

void    Core::playerReady(int userId, int roomId)
{
  std::map<int, User>::iterator it_u = users_.find (userId);
  std::map<int, Room>::iterator it_r = rooms_.find (roomId);
  std::list<const User*>::const_iterator	it;

  if (it_u != users_.end () && (it_u->second).curentRoom_ == roomId && !(it_u->second).ready_)
    {
      (it_u->second).ready_ = true;
      if (it_r != rooms_.end ())
	{
	  (it_r->second).newPlayerReady ();
	  for (it = (it_r->second).getClients ().begin (); it != (it_r->second).getClients ().end (); ++it)
	    nm_.sendToService ((*it)->id_, rm_->treatmentRoomNotifyReady ((it_r->second).getNbReady ()));
	}
    }
}

void    Core::playerConnectionReady(int userId)
{
  std::map<int, User>::iterator it_u = users_.find (userId);

  if (it_u != users_.end () && (it_u->second).ready_)
    {
      std::map<int, Room>::iterator it_r = rooms_.find ((it_u->second).curentRoom_);
      if (it_r != rooms_.end ())
        (it_r->second).newPlayerReady ();
    }
}

void    Core::removeUserFromRoom(int userId, int roomId)
{
  std::map<int, User>::iterator        it_u = users_.find (userId);
  std::map<int, Room>::iterator        it_r = rooms_.find (roomId);
  std::list<const User*>::const_iterator	it;

  if (it_u != users_.end() && it_r != rooms_.end () && (it_r->second).popClient(&it_u->second))
    {
      (it_u->second).ready_ = false;
      roomNotifyPlayer (it_r->second, userId, 1, (it_u->second).name_);
      (it_u->second).curentRoom_ = -1;
      for (it = (it_r->second).getClients ().begin (); it != (it_r->second).getClients ().end (); ++it)
	nm_.sendToService ((*it)->id_, rm_->treatmentRoomNotifyReady ((it_r->second).getNbReady ()));
    }
}

void    Core::createRoom(int userId, std::string const& name, int config)
{
  std::map<int, User>::iterator        it = users_.find (userId);
  std::map<int, Room>::iterator         it_r;

  if (it == users_.end ())
    return;
  if ((it->second).curentRoom_ != -1)
    return;
  rooms_.insert (std::make_pair (maxRoomId, Room (maxRoomId, config, ready_)));
  addUserInRoom (userId, maxRoomId, name);
  ++maxRoomId;
}

const std::map<int, Room> &     Core::getRooms() const
{
  return rooms_;
}

void    Core::createGames()
{
  std::list<int>::iterator      it;
  std::map<int, Room>::iterator it_r;

  for (it = ready_.begin (); it != ready_.end (); it = ready_.erase (it))
    if ((it_r = rooms_.find (*it)) != rooms_.end ())
      {
        if (!(it_r->second).isRunning ())
          {
            if (!createGame (it_r->second))
	      return ;
          }
        else
          launchGame (*it);
      }
}

void    Core::launchGame(int id)
{
  std::map<int, Game*>::iterator        it = games_.find (id);

  if (it == games_.end ())
    return;
  gamePool_.pushTask (it->second);
  gamePool_.addWorker ();
}

bool    Core::createGame(Room& r)
{
  std::list<const User *>::const_iterator       it_c;
  Game                          *g;

  int                           i = 0;
  const std::list<const User *> &    clients = r.getClients ();
  for (it_c = clients.begin (); it_c != clients.end (); ++it_c, ++i)
    nm_.sendToService ((*it_c)->id_, rm_->treatmentRoomStartGame (i));
  try
    {
      g = new Game (r.getClients (), 0, r.getId (), r.getReceivePort (), dones_);
    }
  catch (std::exception & e)
    {
      return false;
    }
  r.setRunning ();
  games_.insert (std::make_pair (r.getId (), g));
  return true;
}

void    Core::returnRoomList(int id)
{
  nm_.sendToService (id, rm_->treatmentRoomList (rooms_));
}
