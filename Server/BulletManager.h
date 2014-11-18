
#pragma once

#include <map>
#include <list>
#include <string>
#include "ABullet.h"
#include "BulletSimple.h"
#include "BulletPlayer0.h"
#include "BulletPlayer1.h"
#include "BulletPlayer2.h"
#include "Pool.h"

class BulletManager
{
private:
  std::map<std::string, Pool<ABullet*> >                bullets_;

private:
  BulletManager();

public:
  BulletManager(std::list<Tile*> & t);
  ~BulletManager();
  ABullet*  Spawn(std::string const& typeName, int idOwner, int x, int y, int angle, int speed);
  void  Destroy(ABullet * bullet);
};
