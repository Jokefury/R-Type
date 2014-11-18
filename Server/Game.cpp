#include "Game.h"
#include "Random.h"

#if defined(_WIN32) || defined(_WIN64)
#include        "WinGameClock.h"
#elif UNIX
#include        "UnixGameClock.h"
#endif

Game::Game(const std::list<const User *> & clients, int, int roomId, int port, SafeQueue<int>& dones) :
  bm_ (tiles_), mm_ (tiles_), ms_ (mm_),  nm_ (clients, port), rm_(players_), dones_ (dones), id_ (roomId)
{
  int   nbPlayers;
  int   id;
  std::list<const User *>::const_iterator it;

  id = 0;
  clock_ = new gameClock ();
  nbPlayers = clients.size ();
  if (nbPlayers > 4)
    nbPlayers = 4;
  for (int i = 0; i < ENV_X + TILE_SIZE; i += TILE_SIZE)
    tiles_.push_back (new Tile (i, i + TILE_SIZE));
  for (it = clients.begin(); it != clients.end() && id != nbPlayers; ++it)
    {
      int       y;

      y = 200 + (id * 50);
	  this->players_.push_back (new Player((*it)->name_, id, 50, y, "player_sprite.png", this->tiles_, (*it)->id_));
      entities_.push_back (players_[id]);
      ++id;
    }
}

Game::~Game()
{
}
static bool incId (const AEntity* first, const AEntity* second)
{
  return ( first->getId() < second->getId() );
}

static bool sameId (const AEntity* first, const AEntity* second)
{
  return ( first->getId() == second->getId() );
}

void  Game::manageCollisions()
{
  std::list<Tile*>::iterator    it;
  std::list<AEntity*>           slains;
  std::list<AEntity*>::iterator it1;

  int i = 0;
  for (it = tiles_.begin (); it != tiles_.end (); ++it)
    {
      (*it)->collide (players_, slains);
      ++i;
    }

  slains.sort (incId);
  slains.unique (sameId);
  for (it1 = slains.begin (); it1 != slains.end (); it1 = slains.erase(it1))
    {
      if ((*it1)->getType() == AEntity::BULLET)
        {
          nm_.sendToServices (rm_.treatmentGameBulletDestroy ((*it1)->getId (), *it1, clock_->getTotalElapsedTime()));
          this->bm_.Destroy(dynamic_cast<ABullet *>(*it1));
          entities_.remove (*it1);
        }
      else if ((*it1)->getType() == AEntity::MOB)
        {
          nm_.sendToServices (rm_.treatmentGameEnemyDestroy ((*it1)->getId (), *it1, clock_->getTotalElapsedTime()));
          this->mm_.Destroy(dynamic_cast<AMob *>(*it1));
          entities_.remove (*it1);
        }
      else
        {
          nm_.sendToServices (rm_.treatmentGamePlayerDestroy ((*it1)->getId (), *it1, clock_->getTotalElapsedTime()));
		  dynamic_cast<Player*>((*it1))->setDeathTime(0);
        }
    }
}


void    Game::manageMobSpawn()
{
  std::list<AEntity*>                   tmp;
  std::list<AEntity*>::iterator         it;

  ms_.Spawn (clock_->getElapsedTime (), tmp);
  for (it = tmp.begin (); it != tmp.end (); ++it)
    {
      nm_.sendToServices (rm_.treatmentGameEnemySpawn ((*it)->getId(), *it, clock_->getTotalElapsedTime()));
      entities_.push_back (*it);
    }
}

void  Game::manageMove()
{
  std::list<AEntity*>::iterator it;
  std::list <Tile *>::iterator  it_t;

  for (it_t = this->tiles_.begin(); it_t != this->tiles_.end(); ++it_t)
    (*it_t)->clearTile();

  for (it = entities_.begin (); it != entities_.end (); ++it)
    {
      if ((*it)->move (clock_->getElapsedTime ()))
        {
          if ((*it)->getType() == AEntity::PLAYER)
            nm_.sendToServices (rm_.treatmentGamePlayerMove ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
          else if ((*it)->getType() == AEntity::MOB)
            nm_.sendToServices (rm_.treatmentGameEnemyMove ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
          else
            nm_.sendToServices (rm_.treatmentGameBulletMove ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
        }
    }
}

void    Game::manageLimits()
{
  std::list<AEntity*>::iterator it;
  std::list<AEntity*>           slains;

  for (it = this->entities_.begin (); it != this->entities_.end (); ++it)
    {
      if ((*it)->getPos().first <= -TILE_SIZE ||
          (*it)->getPos().first >= ENV_X + TILE_SIZE ||
          (*it)->getPos().second <= -(TILE_SIZE / 2) ||
          (*it)->getPos().second >= (ENV_Y - 70))
        slains.push_front(*it);
    }
  for (it = slains.begin (); it != slains.end (); ++it)
    {
      if ((*it)->getType() == AEntity::MOB)
        {
          nm_.sendToServices (rm_.treatmentGameEnemyDestroy ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
          this->mm_.Destroy(dynamic_cast<AMob *>(*it));
          entities_.remove (*it);
        }
      else if ((*it)->getType() == AEntity::BULLET)
        {
          nm_.sendToServices (rm_.treatmentGameBulletDestroy ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
          this->bm_.Destroy(dynamic_cast<ABullet *>(*it));
          entities_.remove (*it);
        }
	  else
	  {
		  nm_.sendToServices (rm_.treatmentGamePlayerDestroy ((*it)->getId (), *it, clock_->getTotalElapsedTime()));
		  (*it)->takeDmg(1);        
		  (*it)->setPos(ENV_X / 2, ENV_Y / 2);
		  dynamic_cast<Player*>((*it))->setDeathTime(0);
	  }
    }
}

void    Game::update()
{
  DataPacket const* packet;
  std::list<AEntity*>::iterator it;
  std::list<BulletInfos*>       bullets;
  std::list<BulletInfos*>::iterator     itb;

  int   id;

  this->clock_->update ();
  this->nm_.wait(20);
  if (this->nm_.recvFromService(id, &packet))
    {
      if (packet)
	this->rm_.treatment(packet);
    }
  for (it = this->entities_.begin (); it != this->entities_.end (); ++it)
    {
      BulletInfos*     itb2;
      AEntity*         tmp;
      bullets = ((*it)->update(this->clock_->getElapsedTime()));
      for (itb = bullets.begin (); itb != bullets.end();)
        {
			if ((tmp = this->bm_.Spawn((*itb)->getName(), (*itb)->getIdOwner(), (*it)->getPos().first + ((*it)->getHitBox().first / 2), (*it)->getPos().second + ((*it)->getHitBox().second / 2), (*itb)->getAngle(), (*itb)->getSpeed ())))
            {
				this->nm_.sendToServices (rm_.treatmentGameBulletSpawn(tmp->getId(), (*itb)->getType() , tmp, clock_->getTotalElapsedTime()));
              entities_.push_back (tmp);
            }
          itb2 = (*itb);
          itb = bullets.erase(itb);
          delete itb2;
        }
    }
  manageMobSpawn ();
}

void    Game::respawnPlayers()
{
  std::vector<Player *>::iterator       it;
  int           x = ENV_X / 2;
  int           y = ENV_Y / 2;

  for (it = this->players_.begin(); it != this->players_.end(); ++it)
    {
      if ((*it)->getLife() > 0)
        {
          x = (*it)->getPos().first;
          y = (*it)->getPos().second;
        }
    }

  for (it = this->players_.begin(); it != this->players_.end(); ++it)
    {
      if ((*it)->getLife() <= 0 && (*it)->getDeathTime() >= 3000)
        {
          (*it)->reInit(x, y, 0);
		  (*it)->setRespawn(true);
		  (*it)->setDeathTime(0);
		  (*it)->addSpaceShip(-1);
          this->nm_.sendToServices (rm_.treatmentGamePlayerSpawn((*it)->getId(), (*it), clock_->getTotalElapsedTime()));
        }
    }
}

bool    Game::gameOver()
{
  std::vector<Player *>::iterator       it;

  for (it = this->players_.begin(); it != this->players_.end(); ++it)
    {
      if ((*it)->getSpaceShip() >= 0)
        return false;
    }
  return true;
}

#include <iostream>

void  Game::run()
{
  std::pair<int, int>   pos;
  unsigned int   i = -1;

  Random::init(this->clock_->getTotalElapsedTime());
  while (++i != this->players_.size())
    nm_.sendToServices (rm_.treatmentGamePlayerSpawn (i, players_[i], clock_->getTotalElapsedTime()));
  i = 0;
  char endResult = 1;

  while (1)
    {
      this->update();
      this->manageMove ();
      this->manageCollisions ();

      this->manageLimits();
      if (this->gameOver())
        {
          endResult = 0;
          break;
        }
      this->respawnPlayers();
    }
  int pts0 = 0;
  int pts1 = 0;
  int pts2 = 0;
  int pts3 = 0;

  int nbPlayers = this->players_.size();
  if (nbPlayers >= 1)
    pts0 = this->players_[0]->getPoints();
  if (nbPlayers >= 2)
    pts1 = this->players_[1]->getPoints();
  if (nbPlayers >= 3)
    pts2 = this->players_[2]->getPoints();
  if (nbPlayers >= 4)
    pts3 = this->players_[3]->getPoints();
  nm_.sendToServices (rm_.treatmentGameNotifyEnd(endResult, pts0, pts1, pts2, pts3, clock_->getTotalElapsedTime()));
  dones_.push (this->id_);
}

void    Game::operator()()
{
  run ();
}
