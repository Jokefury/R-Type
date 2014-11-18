
#include "BulletInfos.h"

BulletInfos::BulletInfos(std::string const& name, int type, int idOwner, int angle, int speed)
  : name_(name), angle_(angle), idOwner_(idOwner), speed_(speed), type_(type)
{
}


BulletInfos::~BulletInfos(void)
{
}

std::string const& BulletInfos::getName() const
{
  return (this->name_);
}

int     BulletInfos::getSpeed() const
{
  return (this->speed_);
}

int     BulletInfos::getAngle() const
{
  return (this->angle_);
}

int BulletInfos::getIdOwner() const
{
  return (this->idOwner_);
}

int BulletInfos::getType() const
{
  return (this->type_);
}
