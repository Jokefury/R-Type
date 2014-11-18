#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>
#include <map>

class FastShooter : public AMob
{
private:
	FastShooter();
	int   lastShot_;
	int	lastRot_;
	int	angleKey_;
	std::map<int, float>	angleMap_;
public:
	FastShooter(int id, std::list<Tile*> & tiles);
	~FastShooter();
	std::list<BulletInfos*> update(int ellapsedTime);
};
