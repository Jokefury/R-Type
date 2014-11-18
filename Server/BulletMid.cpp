#include "BulletMid.h"

BulletMid::BulletMid(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletMid",type, id, 2, 2, COMP, 4, 0, 0, 15, 12, "./Sprites/BulletMid.png", tiles)
{

}

BulletMid::~BulletMid()
{

}

std::list<BulletInfos*> BulletMid::update(int ellapsedTime)
{
  std::list<BulletInfos*>       res;

  (void)ellapsedTime;
  return (res);
}
