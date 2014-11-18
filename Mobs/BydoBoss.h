#pragma once

#include "AMob.h"
#include "BulletInfos.h"
#include <list>

class BydoBoss : public AMob
{
private:
	BydoBoss();
	int	lastShot_;
	int	lastShot2_;
	int	lastRot_;
	int	lastRot2_;
	int	angleKey_;
	int	angleKey2_;

	std::map<int, float>	angleMap_;

public:
	BydoBoss(int id, std::list<Tile*> & tiles);
	~BydoBoss();
	std::list<BulletInfos*> update(int ellapsedTime);
};
