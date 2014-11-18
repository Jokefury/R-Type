#include "Bydo.h"
#include "Random.h"


Bydo::Bydo(int id, std::list<Tile*> & tiles)
	: AMob("Bydo", id, 50, 1, 1, 3, 0, 0, 31, 36, "./Sprite/BydoStd.png", tiles, 1)
{
	this->lastShot_ = 2000;
}

Bydo::~Bydo()
{

}

std::list<BulletInfos*> Bydo::update(int ellapsedTime)
{
	std::list<BulletInfos*>       res;

	this->lastShot_ += ellapsedTime;
	if (this->lastShot_ > 2250)
	{
		if (Random::gen() % 2)
		{
			this->lastShot_ = 0;
			res.push_front(new BulletInfos("BulletSimple", 40, this->getId(), 180, 6));
		}
		else
			this->lastShot_ -= 1000;
	}
	return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
	__declspec(dllexport)
#endif

	AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

	return new Bydo(id, tiles);
}

