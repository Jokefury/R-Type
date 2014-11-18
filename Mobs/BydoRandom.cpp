#include <cstdlib>
#include "BydoRandom.h"
#include "Random.h"

BydoRandom::BydoRandom(int id, std::list<Tile*> & tiles)
	: AMob("BydoRandom",id , 150, 3, 3, 4, 0, 0, 48, 33, "./Sprite/BydoRandom.png", tiles, 2)
{
	this->lastShot_ = 1000;
	this->lastRot_ = 0;
}

BydoRandom::~BydoRandom()
{
	angleKey_ = 0;
	angleMap_[0] = 0;
	angleMap_[1] = 15;
	angleMap_[2] = 30;
	angleMap_[3] = 45;
	angleMap_[4] = 60;
	angleMap_[5] = 75;
	angleMap_[6] = 90;
	angleMap_[7] = 105;
	angleMap_[8] = 120;
	angleMap_[9] = 135;
	angleMap_[10] = 150;
	angleMap_[11] = 165;
	angleMap_[12] = 180;
	angleMap_[13] = 195;
	angleMap_[14] = 210;
	angleMap_[15] = 225;
	angleMap_[16] = 240;
	angleMap_[17] = 255;
	angleMap_[18] = 270;
	angleMap_[19] = 285;
	angleMap_[20] = 300;
	angleMap_[21] = 315;
	angleMap_[22] = 330;
	angleMap_[23] = 345;
}

std::list<BulletInfos*> BydoRandom::update(int ellapsedTime)
{
	std::list<BulletInfos*>       res;

	this->lastShot_ += ellapsedTime;
	if (this->lastShot_ > 1500)
	{
	if (Random::gen() % 2)
		{
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), this->angleMap_[Random::gen() % 24], 6));
			this->lastShot_ = 0;
		}
		else
			this->lastShot_ -= 1000;
	}
	this->lastRot_ += ellapsedTime;
		if (this->lastRot_ >= 500)
		{
			this->lastRot_ = 0;
			this->setMovement(this->angleMap_[(Random::gen() % 7) + 9]);
		}
	return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
	__declspec(dllexport)
#endif

	AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

	return new BydoRandom(id, tiles);
}

