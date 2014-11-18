#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>
#include<map>

class BydoZigZag : public AMob
{
private:
	BydoZigZag();
	int   lastShot_;
	int	lastRot_;
	int	angleKey_;
	std::map<int, float>	angleMap_;
public:
	BydoZigZag(int id, std::list<Tile*> & tiles);
	~BydoZigZag();
	std::list<BulletInfos*> update(int ellapsedTime);
};
