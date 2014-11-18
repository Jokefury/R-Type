#include "BydoZigZag.h"
#include <map>
#include "Random.h"

BydoZigZag::BydoZigZag(int id, std::list<Tile*> & tiles)
	: AMob("BydoZigZag",id , 75, 1, 1, 5, 0, 0, 31, 36, "./Sprite/BydoStd.png", tiles, 1)

{
	this->lastShot_ = 2000;
	this->lastRot_ = 0;
	angleKey_ = 0;
	angleMap_[0] = 120;
	angleMap_[1] = 150;
	angleMap_[2] = 180;
	angleMap_[3] = 210;
	angleMap_[4] = 240;
	angleMap_[5] = 240;
	angleMap_[6] = 210;
	angleMap_[7] = 150;
	angleMap_[8] = 150;
	angleMap_[9] = 120;
}

BydoZigZag::~BydoZigZag()
{

}

std::list<BulletInfos*> BydoZigZag::update(int ellapsedTime)
{
	std::list<BulletInfos*>       res;

	this->lastShot_ += ellapsedTime;
	if (this->lastShot_ > 1700)
	{
	  if (Random::gen() % 2)
		{
			this->lastShot_ = 0;
			res.push_front(new BulletInfos("BulletSimple", 40, this->getId(), 180, 5));
		}
		else
			this->lastShot_ -= 1000;
	}

	this->lastRot_ += ellapsedTime;
	if (this->lastRot_ >= 333)
	{
		this->lastRot_ = 0;
		this->setMovement(this->angleMap_[this->angleKey_]);
		this->angleKey_++;
	}
	if (this->angleKey_ >= 10)
		this->angleKey_ = 0;

	return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
	__declspec(dllexport)
#endif

	AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

	return new BydoZigZag(id, tiles);
}

