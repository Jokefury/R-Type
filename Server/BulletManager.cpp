#include "BulletManager.h"
#include <map>
#include <list>
#include <string>
#include <algorithm>

BulletManager::BulletManager(std::list<Tile*> & t)
{
  int   id;
  int   i;

  id = 1000;
  for (i = -1; i < 500; ++i)
    {
      this->bullets_["BulletSimple"].pushElement(new BulletSimple(40, id, t));
      ++id;
    }
  for (i = -1; i < 300; ++i)
    {
      this->bullets_["BulletMid"].pushElement(new BulletSimple(41, id, t));
      ++id;
    }
  for (i = -1; i < 100; ++i)
    {
      this->bullets_["BulletHeavy"].pushElement(new BulletSimple(42, id, t));
      ++id;
    }
  for (i = -1; i < 400; ++i)
    {
      this->bullets_["BulletPlayer0"].pushElement(new BulletPlayer0(0, id, t));
      ++id;
    }
  for (i = -1; i < 200; ++i)
    {
      this->bullets_["BulletPlayer1"].pushElement(new BulletPlayer1(1, id, t));
      ++id;
    }
  for (i = -1; i < 200; ++i)
    {
      this->bullets_["BulletPlayer2"].pushElement(new BulletPlayer2(2, id, t));
      ++id;
    }
}


BulletManager::~BulletManager()
{

}

ABullet*    BulletManager::Spawn(std::string const& typeName, int idOwner, int x, int y, int angle, int speed)
{
  ABullet*      tmp;

  tmp = this->bullets_[typeName].getElement();
  if (!tmp)
    return 0;
  tmp->setIdOwner (idOwner);
  tmp->reInit (x, y, angle);
  tmp->setSpeed(speed);
  return tmp;
}

void    BulletManager::Destroy(ABullet * bullet)
{
  if (bullet)
    this->bullets_[bullet->getName()].pushElement(bullet);
}
