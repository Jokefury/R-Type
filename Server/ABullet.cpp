
#include "ABullet.h"

ABullet::ABullet(std::string const& name, int BType, int id, int dmg, int life,
		 eTeam team, int speed, int x, int y, int xHB, int yHB,
		 std::string const& spritePath, std::list<Tile*> & tiles)
  : AEntity(BULLET, id, dmg, life, team, speed, x, y, xHB, yHB, spritePath, tiles)
{
  this->name_ = name;
  this->idOwner_ = -1;
  isMoving_ = true;
  this->BType_ = BType;
}


ABullet::~ABullet(void)
{
}

void	ABullet::setBType(int BType)
{
  this->BType_ = BType;
}

int	ABullet::getBType() const
{
  return (this->BType_);
}

std::string const& ABullet::getName() const
{
  return (this->name_);
}

int     ABullet::getIdOwner() const
{
  return (idOwner_);
}

void    ABullet::setIdOwner(int id)
{
  this->idOwner_ = id;
}
