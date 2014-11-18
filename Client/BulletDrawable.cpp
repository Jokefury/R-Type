#define _USE_MATH_DEFINES

#include <math.h>
#include "BulletDrawable.h"

static const int gIntRecs[3][4] = {
  {249, 105, 265, 113},
  {233, 120, 265, 132},
  {220, 136, 265, 150},
};

BulletDrawable::BulletDrawable(sf::Image const& img, sf::RenderWindow* ptr, int type)
	: win_(ptr), elapsedTime_(0), alternateMove_(false)
{
	this->sprite_.SetImage(img);
	this->sprite_.SetSubRect(sf::IntRect(gIntRecs[type][0],
					     gIntRecs[type][1],
					     gIntRecs[type][2],
					     gIntRecs[type][3]));
	this->width_ = this->sprite_.GetSize().x;
	this->height_ = this->sprite_.GetSize().y;
	this->cl_.Reset();
	this->sprite_.SetScale(1.5, 1.5);
}

bool BulletDrawable::EndingAnim() const
{
	return false;
}

void BulletDrawable::animate(float angle)
{
	this->sprite_.SetRotation(angle);
}

void BulletDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}


float BulletDrawable::getTimeInMs()
{
	float elapsed;
	elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void BulletDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void BulletDrawable::setPosY(int y)
{
	this->posY_ = y;
}

BulletDrawable::~BulletDrawable()
{
}
