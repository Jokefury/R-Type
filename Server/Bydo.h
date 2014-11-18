
#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>

class Bydo : public AMob
{
private:
  int   lastShot_;

private:
  Bydo();

public:
  Bydo(int id, std::list<Tile*> & tiles);
  virtual ~Bydo();
  virtual std::list<BulletInfos*> update(int ellapsedTime);
};
