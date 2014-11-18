
#include "BulletPlayer0.h"

BulletPlayer0::BulletPlayer0(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletPlayer0", type, id, 1, 1, HUMAN, 16, 0, 0, 24, 12, "./Sprites/BulletPlayer0.png", tiles)
{

}

BulletPlayer0::~BulletPlayer0()
{
}

std::list<BulletInfos*> BulletPlayer0::update(int)
{
  std::list<BulletInfos*>       res;

  return (res);
}
