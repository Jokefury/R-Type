#pragma once

#include <string>
#include "ABullet.h"

class BulletPlayer0 : public ABullet
{
private:
  BulletPlayer0();
  
public:
  BulletPlayer0(int type, int id, std::list<Tile*> & tiles);
  virtual ~BulletPlayer0();
  virtual std::list<BulletInfos*> update(int ellapsedTime);

};

