#include        <cstdlib>
#include        "MobSpawner.h"
#include        "Random.h"

MobSpawner::MobSpawner(MobManager & mm) :
total_ (100), mm_ (mm), levels_ (mm.getMobsLevels ()), elapsedTime_ (0), hardness_ (0), totalTime_(0), waitDelay_ (60000), waitDuration_ (30000), lastPop_ (0), state_ (GENERATING), cloudMode_ (false), cloudType_ (""), cloudNb_ (0), lastCloudSpawn_ (0), cloudPos_ (0)
{

	this->hardnessMap_[0] = 15000;
	this->hardnessMap_[1] = 30000;
	this->hardnessMap_[2] = 45000;
	this->hardnessMap_[3] = 60000; // Event boss
	this->hardnessMap_[4] = 90000;
	this->hardnessMap_[5] = 120000;
	this->hardnessMap_[6] = 150000; // Event boss + 3 x2
	this->hardnessMap_[7] = 180000;
	this->hardnessMap_[8] = 210000;
	this->hardnessMap_[9] = 240000; // Event boss x2
	this->hardnessMap_[10] = 270000; // HC
	this->hardnessMap_[11] = 999999999; // HC

	this->HcMap_[0] = &MobSpawner::hdLvl0;
	this->HcMap_[1] = &MobSpawner::hdLvl1;
	this->HcMap_[2] = &MobSpawner::hdLvl2;
	this->HcMap_[3] = &MobSpawner::hdLvl3;
	this->HcMap_[4] = &MobSpawner::hdLvl4;
	this->HcMap_[5] = &MobSpawner::hdLvl5;
	this->HcMap_[6] = &MobSpawner::hdLvl6;
	this->HcMap_[7] = &MobSpawner::hdLvl7;
	this->HcMap_[8] = &MobSpawner::hdLvl8;
	this->HcMap_[9] = &MobSpawner::hdLvl9;
	this->HcMap_[10] = &MobSpawner::hdLvl10;
	this->HcMap_[11] = &MobSpawner::hdLvlHC;

	MobSpawner::hdLvl0();
}

MobSpawner::~MobSpawner()
{
}


void	MobSpawner::hdLvl0(void)
{
	mobSpawnChances_[1] = 80;
	mobSpawnChances_[2] = 100;
	mobSpawnChances_[3] = 101;
	mobSpawnChances_[4] = 101;
}

void	MobSpawner::hdLvl1(void)
{
	mobSpawnChances_[1] = 65;
	mobSpawnChances_[2] = 100;
	mobSpawnChances_[3] = 101;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl2(void)
{
	mobSpawnChances_[1] = 55;
	mobSpawnChances_[2] = 95;
	mobSpawnChances_[3] = 100;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl3(void)
{
	mobSpawnChances_[1] = 50;
	mobSpawnChances_[2] = 90;
	mobSpawnChances_[3] = 100;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl4(void)
{
	mobSpawnChances_[1] = 45;
	mobSpawnChances_[2] = 85;
	mobSpawnChances_[3] = 100;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl5(void)
{
	mobSpawnChances_[1] = 40;
	mobSpawnChances_[2] = 80;
	mobSpawnChances_[3] = 101;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl6(void)
{
	mobSpawnChances_[1] = 35;
	mobSpawnChances_[2] = 70;
	mobSpawnChances_[3] = 101;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl7(void)
{
	mobSpawnChances_[1] = 30;
	mobSpawnChances_[2] = 65;
	mobSpawnChances_[3] = 101;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl8(void)
{
	mobSpawnChances_[1] = 25;
	mobSpawnChances_[2] = 60;
	mobSpawnChances_[3] = 98;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl9(void)
{
	mobSpawnChances_[1] = 10;
	mobSpawnChances_[2] = 50;
	mobSpawnChances_[3] = 95;
	mobSpawnChances_[4] = 101;
}
void	MobSpawner::hdLvl10(void)
{
	mobSpawnChances_[1] = 5;
	mobSpawnChances_[2] = 45;
	mobSpawnChances_[3] = 90;
	mobSpawnChances_[4] = 101;
}

void	MobSpawner::hdLvlHC(void)
{
	mobSpawnChances_[1] = 5;
	mobSpawnChances_[2] = 15;
	mobSpawnChances_[3] = 75;
	mobSpawnChances_[4] = 101;
}

bool   MobSpawner::checkWaiting(std::list<AEntity*>& entities_)
{

	if (state_ == WAITING)
	{
		if (elapsedTime_ > waitDuration_)
		{
			state_ = GENERATING;
			elapsedTime_ = 0;
			lastPop_ = 0;
			return false;
		}
		return true;
	}
	if (elapsedTime_ > waitDelay_)
	{
		std::map<int, std::vector<std::string> >::const_iterator		it;
		std::string                                                   mobName;
		AEntity*                                                      tmp;
		state_= WAITING;
		it = levels_.find (4);
		mobName = it->second[Random::gen() % (it->second.size())];
		if ((tmp = mm_.Spawn (mobName, 810, 225, 180)))
			entities_.push_back (tmp);
		elapsedTime_ = 0;
		return true;
	}
	return false;
}

bool    MobSpawner::checkCloudMode(std::list<AEntity*>& entities_)
{
	AEntity*                                                      tmp;

	if (!cloudMode_)
		return false;
	if (cloudNb_ <= 0)
	{
		cloudMode_ = false;
		return false;
	}
	if (elapsedTime_ - lastCloudSpawn_ > 500)
	{
		lastCloudSpawn_ = elapsedTime_;
		int r = Random::gen() % 3;
		r -= 1;
		cloudPos_ += 30 * r;
		lastPop_ = elapsedTime_;
		if ((tmp = mm_.Spawn (cloudType_, 840, cloudPos_, 180)))
			entities_.push_back (tmp);
		--cloudNb_;
	}
	return true;
}

void    MobSpawner::choseMob(std::list<AEntity*>& entities_, int rnd)
{
	int       yposmob = ((Random::gen() % 9) + 1) * 50;
	AEntity*                                                      tmp;
	std::map<int, int>::const_iterator                            it;
	std::map<int, std::vector<std::string> >::const_iterator        it1;
	std::string                                                   mobName;
	int   i = 0;
	int   cloudRnd = rnd;

	rnd %= total_;
	for (it = mobSpawnChances_.begin(); it != mobSpawnChances_.end () && it->second < rnd; ++it, ++i);
	if (it == mobSpawnChances_.end ())
		return;

	if ((it1 = levels_.find (it->first)) == levels_.end ())
	{  
		return;
	}
	mobName = (it1->second)[cloudRnd % (it1->second).size ()];
	if ((tmp = mm_.Spawn (mobName, 840, yposmob, 180)))
		entities_.push_back (tmp);


	if (it->first != 4)
	{
		cloudMode_ = true;
		cloudType_ = mobName;
		int rr = Random::gen() % 3;
		cloudNb_ = rr + ((hardness_ + 2) / 2) - (it->first * 2);
		lastCloudSpawn_ = elapsedTime_;
		cloudPos_ = yposmob;
	}
}

void    MobSpawner::Spawn(int elapsedTime, std::list<AEntity*>& entities_)
{
	int           rnd = Random::gen();
	int           diff;

	elapsedTime_ += elapsedTime;
	totalTime_ += elapsedTime;

	if (totalTime_ >= hardnessMap_[hardness_] && hardness_ < 11)
	{
		hardness_++;
		(this->*HcMap_[hardness_])();
	}


	if (checkCloudMode (entities_))
		return;
	if (checkWaiting (entities_))
		return;

	diff = elapsedTime_ - lastPop_;
	if (diff > 1500 - (hardness_ * 100))
	{
		lastPop_ = elapsedTime_;
		choseMob (entities_, rnd);
	}
}
