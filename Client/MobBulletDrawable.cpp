#include "MobBulletDrawable.h"

#define _USE_MATH_DEFINES

#include <math.h>

static const int gIntRecs[3][4] = {
  {314, 279, 320, 285},
  {295, 278, 305, 286},
  {277, 277, 289, 287},
};

MobBulletDrawable::MobBulletDrawable(sf::Image const& img, sf::RenderWindow* ptr, int type)
	: win_(ptr), elapsedTime_(0), alternateMove_(false)
{	
	this->sprite_.SetImage(img);
	this->sprite_.SetSubRect(sf::IntRect(gIntRecs[type % 3][0],
					     gIntRecs[type % 3][1],
					     gIntRecs[type % 3][2],
					     gIntRecs[type % 3][3]));
	this->width_ = this->sprite_.GetSize().x;
	this->height_ = this->sprite_.GetSize().y;
	this->cl_.Reset();
	this->sprite_.SetScale(1.5, 1.5);
}

MobBulletDrawable::~MobBulletDrawable()
{
}

bool MobBulletDrawable::EndingAnim() const
{
	return false;
}

void MobBulletDrawable::animate(float angle)
{
	this->sprite_.SetRotation(angle);
}

void MobBulletDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}


float MobBulletDrawable::getTimeInMs()
{
	float elapsed;
	elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void MobBulletDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void MobBulletDrawable::setPosY(int y)
{
	this->posY_ = y;
}
