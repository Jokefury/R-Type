#pragma once
#include <string>
#include "ABullet.h"

class BulletHeavy : public ABullet
{
 private:
  BulletHeavy();
 public:
  BulletHeavy(int type, int id, std::list<Tile*> & tiles);
  ~BulletHeavy();
  std::list<BulletInfos*> update(int ellapsedTime);

};

