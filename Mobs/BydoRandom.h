#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>

class BydoRandom : public AMob
{
private:
  BydoRandom();
  int	lastShot_;
  int	lastRot_;
	int	angleKey_;
	
	std::map<int, float>	angleMap_;

 public:
  BydoRandom(int id, std::list<Tile*> & tiles);
  ~BydoRandom();
  std::list<BulletInfos*> update(int ellapsedTime);
};
