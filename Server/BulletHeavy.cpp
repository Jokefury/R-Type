#include "BulletHeavy.h"

BulletHeavy::BulletHeavy(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletHeavy",type, id, 3, 3, COMP, 4, 0, 0, 18, 15, "./Sprites/BulletMid.png", tiles)
{

}

BulletHeavy::~BulletHeavy()
{

}

std::list<BulletInfos*> BulletHeavy::update(int ellapsedTime)
{
  std::list<BulletInfos*>       res;

  (void)ellapsedTime;
  return (res);
}
