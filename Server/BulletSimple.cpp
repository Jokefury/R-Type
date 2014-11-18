#include "BulletSimple.h"

BulletSimple::BulletSimple(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletSimple",type, id, 1, 1, COMP, 4, 0, 0, 9, 9, "./Sprites/BulletSimple.png", tiles)
{

}

BulletSimple::~BulletSimple()
{

}

std::list<BulletInfos*> BulletSimple::update(int)
{
  std::list<BulletInfos*>       res;

  return (res);
}
