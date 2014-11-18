#define _USE_MATH_DEFINES

#include <math.h>
#include "SFMLDrawable.h"
#include <iostream>

SFMLDrawable::SFMLDrawable(sf::Image const& img, sf::RenderWindow* ptr)
	: win_(ptr), elapsedTime_(0), alternateMove_(false)
{
	this->sprite_.SetImage(img);
	this->width_ = this->sprite_.GetSize().x;
	this->height_ = this->sprite_.GetSize().y;
	this->cl_.Reset();
}

SFMLDrawable::~SFMLDrawable()
{
}

bool SFMLDrawable::EndingAnim() const
{
	return false;
}

void SFMLDrawable::animate(float)
{
}

void SFMLDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}

float SFMLDrawable::getTimeInMs()
{
	float elapsed;
	elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void SFMLDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void SFMLDrawable::setPosY(int y)
{
	this->posY_ = y;
}