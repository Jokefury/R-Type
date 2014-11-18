#include <cstdlib>
#include "BydoStd.h"
#include "Random.h"

BydoStd::BydoStd(int id, std::list<Tile*> & tiles)
	: AMob("BydoStd",id , 125, 3, 3, 4, 0, 0, 48, 33, "./Sprite/BydoStd.png", tiles, 2)
{
	this->lastShot_ = 1000;
	this->ShotNb_ = 1;
}

BydoStd::~BydoStd()
{

}

std::list<BulletInfos*> BydoStd::update(int ellapsedTime)
{
	std::list<BulletInfos*>       res;

	this->lastShot_ += ellapsedTime;
	if (this->lastShot_ > 2500)
	{
		this->lastShot_ = 0; 
		this->ShotNb_ = Random::gen() % 6;
		if (this->ShotNb_ == 2)
		{
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 180, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 135, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 225, 6));
		}
		if (this->ShotNb_ == 1)
		{
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 180, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 150, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 205, 6));
		}
		if (this->ShotNb_ == 0)
		{
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 180, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 195, 6));
			res.push_front(new BulletInfos("BulletMid", 41, this->getId(), 165, 6));
		}
		if (ShotNb_ > 3)
			this->lastShot_ -= 1500;
	}
	return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
	__declspec(dllexport)
#endif

	AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

	return new BydoStd(id, tiles);
}

