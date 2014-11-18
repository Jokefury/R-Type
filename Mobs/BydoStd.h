#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>

class BydoStd : public AMob
{
private:
  BydoStd();
  int	lastShot_;
  int	ShotNb_;
 public:
  BydoStd(int id, std::list<Tile*> & tiles);
  ~BydoStd();
  std::list<BulletInfos*> update(int ellapsedTime);
};
