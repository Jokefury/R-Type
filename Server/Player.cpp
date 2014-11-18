#include "Player.h"

Player::Player(std::string const& name, int id, int x, int y, std::string const& spritePath,
	std::list<Tile*> & tiles, int socketId)
	: AEntity(PLAYER, id, 1, 1, HUMAN, 5, x, y , 48, 21, spritePath, tiles),
	lastShot_ (500), deathTime_(5000), lvl_(1), spaceShip_(2), socketId_(socketId)
{
	this->name_ = name;
	this->respawn_ = false;
	this->isMoving_ = false;
	this->points_ = 0;
	this->XpMap_[1] = 1000;
	this->XpMap_[2] = 3000;
	this->XpMap_[3] = 6000;
	this->XpMap_[4] = 10000;
	this->XpMap_[5] = 15000;
	this->XpMap_[6] = 21000;
	this->XpMap_[7] = 28000;

	this->fireMap_[1] = &Player::fireLvl1;
	this->fireMap_[2] = &Player::fireLvl2;
	this->fireMap_[3] = &Player::fireLvl3;
	this->fireMap_[4] = &Player::fireLvl4;
	this->fireMap_[5] = &Player::fireLvl5;
	this->fireMap_[6] = &Player::fireLvl6;
	this->fireMap_[7] = &Player::fireLvl7;
}

Player::~Player(void)
{
}

void	Player::setRespawn(bool r)
{
	this->respawn_ = r;
}

bool	Player::getRespawn() const
{
	return (this->respawn_);
}

void	Player::fireLvl1(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 250 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 0, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;
}

void	Player::fireLvl2(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 250 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 15, 17));
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 345, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;

}

void	Player::fireLvl3(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 250 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 0, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;

}

void	Player::fireLvl4(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 250 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 30, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 0, 17));
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 330, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;
}

void	Player::fireLvl5(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 200 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 30, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 0, 17));
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 180, 17));
		bullets.push_front(new BulletInfos("BulletPlayer0", this->getId() * 10, this->getId(), 330, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;
}

void	Player::fireLvl6(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 200 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 30, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 0, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10), this->getId(), 180, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 330, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;
}

void	Player::fireLvl7(std::list<BulletInfos*>& bullets)
{
	if (this->lastShot_ >= 200 )
	{
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 30, 17));
		bullets.push_front(new BulletInfos("BulletPlayer2", (this->getId() * 10) + 2, this->getId(), 0, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 180, 17));
		bullets.push_front(new BulletInfos("BulletPlayer1", (this->getId() * 10) + 1, this->getId(), 330, 17));
		this->lastShot_ = 0;
	}
	this->bulletShot_ = false;
}

int	Player::getSpaceShip() const
{
	return(this->spaceShip_);
}

void	Player::setSpaceShip(int spaceShip)
{
	this->spaceShip_ = spaceShip;
}

int	Player::addSpaceShip(int spaceShip)
{
	this->spaceShip_ += spaceShip;
	return (this->spaceShip_);
}


std::string const& Player::getName() const
{
	return (this->name_);
}

int Player::getSocketId() const
{
	return this->socketId_;
}

void    Player::setDeathTime(int time)
{
	this->deathTime_ = time;
}

int     Player::getDeathTime() const
{
	return (this->deathTime_);
}

int     Player::addPoints(int points)
{
	this->points_ += points;
	return(this->points_);
}

int     Player::getPoints() const
{
	return (this->points_);
}

void    Player::setPoints(int points)
{
	this->points_ = points;
}

std::list<BulletInfos*>       Player::update(int ellapsedTime)
{
	std::list<BulletInfos*>       tmp;

	this->deathTime_ += ellapsedTime;
	this->lastShot_ += ellapsedTime;
	if (this->deathTime_ >= 3000 && this->respawn_)
		this->respawn_ = false;

	if (this->lvl_ < 7 && this->getPoints() >= this->XpMap_[this->lvl_] )
		this->lvl_++;

	if (this->bulletShot_ &&  this->getLife() > 0)
		(this->*fireMap_[this->lvl_])(tmp);
	return (tmp);
}
