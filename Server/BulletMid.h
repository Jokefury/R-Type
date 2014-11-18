#pragma once
#include <string>
#include "ABullet.h"

class BulletMid : public ABullet
{
 private:
  BulletMid();
 public:
  BulletMid(int type, int id, std::list<Tile*> & tiles);
  ~BulletMid();
  std::list<BulletInfos*> update(int ellapsedTime);

};

