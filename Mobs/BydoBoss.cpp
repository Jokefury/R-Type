#include <cstdlib>
#include "BydoBoss.h"
#include "Random.h"

BydoBoss::BydoBoss(int id, std::list<Tile*> & tiles)
	: AMob("BydoBoss",id , 1000, 50, 50, 1, 0, 0, 91, 49, "./Sprite/BydoStd.png", tiles, 4)

{
	this->lastShot_ = 1000;
	this->lastShot2_ = 1000;
	this->lastRot_ = 0;
	this->angleKey_ = 0;
	this->angleKey2_ = 12;

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

BydoBoss::~BydoBoss()
{

}

std::list<BulletInfos*> BydoBoss::update(int ellapsedTime)
{
	std::list<BulletInfos*>       res;
	this->lastShot_ += ellapsedTime;
	this->lastShot2_ += ellapsedTime;

	if (this->lastShot_ > 500)
	{


		this->lastShot_ = 0;
		res.push_front(new BulletInfos("BulletMid", 41, this->getId(), this->angleMap_[this->angleKey_], 7));
		res.push_front(new BulletInfos("BulletMid", 41, this->getId(), this->angleMap_[this->angleKey2_], 7));
		this->angleKey_++;
		this->angleKey2_--;
		if (this->angleKey_ >= 24)
			this->angleKey_ = 0;
		if (this->angleKey2_ < 0)
			this->angleKey2_ = 23;
	}
	
	if (this->lastShot2_ > 1000)
	{
		int angleRand = Random::gen() % 24;
		res.push_front(new BulletInfos("BulletHeavy", 42, this->getId(), this->angleMap_[angleRand], 5));
		this->lastShot2_ = 0;
	}

	if (this->getPos().first < 250 && this->getAngle() != 0)
		this->setMovement(0);
	if (this->getPos().first > 350 && this->getAngle() != 180)
		this->setMovement(180);

	return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
	__declspec(dllexport)
#endif

	AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

	return new BydoBoss(id, tiles);
}

