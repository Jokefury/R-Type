#include "FastShooter.h"
#include <map>

FastShooter::FastShooter(int id, std::list<Tile*> & tiles)
  : AMob("FastShooter",id , 200, 9, 9, 5, 0, 0, 84, 70, "./Sprite/BydoStd.png", tiles, 3)

{
  this->lastShot_ = 2000;
  this->lastRot_ = 0;
  angleKey_ = 0;
  angleMap_[0] = 120;
  angleMap_[1] = 135;
  angleMap_[2] = 150;
  angleMap_[3] = 165;
  angleMap_[4] = 180;
  angleMap_[5] = 195;
  angleMap_[6] = 210;
  angleMap_[7] = 225;
  angleMap_[8] = 240;
  angleMap_[9] = 225;
  angleMap_[10] = 210;
  angleMap_[11] = 195;
  angleMap_[12] = 180;
  angleMap_[13] = 195;
  angleMap_[14] = 165;
  angleMap_[15] = 150;
  angleMap_[16] = 135;
}

FastShooter::~FastShooter()
{

}

std::list<BulletInfos*> FastShooter::update(int ellapsedTime)
{
  std::list<BulletInfos*>       res;

  this->lastShot_ += ellapsedTime;
  if (this->lastShot_ > 333)
    {
      this->angleKey_++;
      res.push_front(new BulletInfos("BulletSimple", 40, this->getId(), this->angleMap_[this->angleKey_], 8));
	   this->lastShot_ = 0;
      if (this->angleKey_ >= 17)
        this->angleKey_ = 0;
    }

  return (res);
}

extern "C"

#if defined (WIN64) || defined (WIN32)
__declspec(dllexport)
#endif

AMob * entryPoint(int id, std::list<Tile*> & tiles)
{

  return new FastShooter(id, tiles);
}

