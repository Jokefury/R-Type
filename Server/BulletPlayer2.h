#pragma once

#include <string>
#include "ABullet.h"

class BulletPlayer2 : public ABullet
{
private:
  BulletPlayer2();

public:
  BulletPlayer2(int type, int id, std::list<Tile*> & tiles);
  virtual ~BulletPlayer2();
  virtual std::list<BulletInfos*> update(int ellapsedTime);

};

