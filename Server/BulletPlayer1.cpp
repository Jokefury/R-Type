
#include "BulletPlayer1.h"

BulletPlayer1::BulletPlayer1(int type, int id, std::list<Tile*> & tiles)
  :ABullet("BulletPlayer1", type, id, 3, 3, HUMAN, 20, 0, 0, 48, 18, "./Sprites/BulletPlayer1.png", tiles)
{

}

BulletPlayer1::~BulletPlayer1()
{
}

std::list<BulletInfos*> BulletPlayer1::update(int)
{
  std::list<BulletInfos*>	res;

  return (res);
}
