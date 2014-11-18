
#include "BulletPlayer2.h"

BulletPlayer2::BulletPlayer2(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletPlayer2", type, id, 6, 6, HUMAN, 20, 0, 0, 67, 21, "./Sprites/BulletPlayer2.png", tiles)
{
}

BulletPlayer2::~BulletPlayer2()
{
}

std::list<BulletInfos*> BulletPlayer2::update(int)
{
  std::list<BulletInfos*>	res;
  
  return (res);
}
