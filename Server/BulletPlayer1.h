#pragma once

#include <string>
#include "ABullet.h"

class BulletPlayer1 : public ABullet
{
private:
  BulletPlayer1();
  
public:
  BulletPlayer1(int type, int id, std::list<Tile*> & tiles);
  virtual ~BulletPlayer1();
  virtual std::list<BulletInfos*> update(int ellapsedTime);

};

