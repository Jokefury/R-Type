#pragma once

#include <string>
#include "ABullet.h"

class BulletSimple : public ABullet
{
private:
  BulletSimple();

public:
  BulletSimple(int type, int id, std::list<Tile*> & tiles);
  virtual ~BulletSimple();
  virtual std::list<BulletInfos*> update(int ellapsedTime);
  
};

