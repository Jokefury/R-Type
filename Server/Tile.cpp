
#include <algorithm>
#include "Tile.h"
#include "Player.h"
#include "AMob.h"
#include "ABullet.h"

Tile::Tile(int xBeg, int xEnd)
  : xBeg_ (xBeg), xEnd_ (xEnd)
{
}

Tile::~Tile(void)
{
}

void    Tile::collide(std::vector<Player*> & players, std::list<AEntity*> & slains)
{
  std::list<AEntity*>::iterator it;

  for (it = this->entities_.begin(); it != this->entities_.end();)
    {
      std::list<AEntity*>::iterator     it2 = it;
      ++it2;
      while (it2 != this->entities_.end())
	{
	  if ((!((*it)->getType() == AEntity::BULLET && (*it2)->getType() == AEntity::BULLET)) && ((*it)->getTeam() != (*it2)->getTeam()))
	    if ((*it)->collide(*it2))
	      {
		(*it)->takeDmg((*it2)->getDmg());
		(*it2)->takeDmg((*it)->getDmg());
		if ((*it)->getType() == AEntity::BULLET && (*it)->getTeam() == HUMAN && (*it2)->getLife() <= 0 && (*it2)->getType() == AEntity::MOB)
		  players[dynamic_cast<ABullet*>((*it))->getIdOwner()]->addPoints(dynamic_cast<AMob*>((*it2))->getPoints());
		if ((*it2)->getType() == AEntity::BULLET && (*it2)->getTeam() == HUMAN && (*it)->getLife() <= 0 && (*it)->getType() == AEntity::MOB)
		  players[dynamic_cast<ABullet*>((*it2))->getIdOwner()]->addPoints(dynamic_cast<AMob*>((*it))->getPoints());
	      }
	  ++it2;
	}
      if ((*it)->getLife () <= 0)
	{
	  slains.push_back (*it);
	  it = entities_.erase (it);
	}
      else
	++it;
    }
}

void Tile::clearTile()
{
  this->entities_.clear();
}


void    Tile::pushEntity(AEntity* entity)
{
  this->entities_.push_front(entity);
  this->entities_.unique();
}

bool    Tile::popEntity(AEntity* entity)
{
  std::list<AEntity*>::iterator it;

  if ((it = std::find (entities_.begin (), entities_.end (), entity)) != entities_.end ())
    {
      entities_.erase(it);
      return true;
    }
  return false;
}

int Tile::getXBeg() const
{
  return xBeg_;
}

int     Tile::getXEnd() const
{
  return xEnd_;
}
