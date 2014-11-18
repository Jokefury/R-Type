
#include "AMob.h"

AMob::AMob(std::string const& name, int id, int points, int dmg, int life, int speed,
	   int x, int y, int xHB, int yHB, std::string const& spritePath,
	   std::list<Tile*> & tiles, int level)
  : AEntity(MOB, id, dmg, life, COMP, speed, x, y, xHB, yHB, spritePath, tiles), level_ (level)
{
  this->name_ = name;
  this->points_ = points;
}


AMob::~AMob(void)
{
}

int AMob::getPoints(void) const
{
  return (this->points_);
}

std::string const& AMob::getName(void) const
{
  return (this->name_);
}

int     AMob::getLevel() const
{
  return level_;
}
