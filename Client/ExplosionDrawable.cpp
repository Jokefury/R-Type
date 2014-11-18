#include "ExplosionDrawable.h"
#include <iostream>

ExplosionDrawable::ExplosionDrawable(sf::Image const& img, sf::RenderWindow* ptr)
	: win_(ptr), elapsedTime_(0), animating_(false)
{
	this->sprite_.SetImage(img);
	this->sprite_.SetSubRect(sf::IntRect(267,304,285,319));
	this->width_ = 460;
	this->height_ = 326;
	this->cl_.Reset();
	this->x_ = 1;
	this->y_ = 3;
	this->sprite_.SetScale(1.5, 1.5);
}

ExplosionDrawable::~ExplosionDrawable()
{
}

bool ExplosionDrawable::EndingAnim() const
{
	return this->animating_;
}

void ExplosionDrawable::animate(float)
{
	if (this->animating_ == false)
	{
		int x_to = 256 - this->x_ *(256 / 4);
		int x_from = x_to - (256/4);
		int y_to = 256 - this->y_ *(256 / 4);
		int y_from = y_to  - (256 / 4);

		sprite_.SetSubRect(sf::IntRect(x_from, y_from, x_to, y_to));
		if (this->elapsedTime_ >= 75)
		{
			this->elapsedTime_ = 0;
			this->x_++;
		}	 
		if (this->x_ >= 4 )
		{
			this->elapsedTime_ = 0;
			this->x_ = 1;
			this->y_--;
		}
		if (this->y_ <= 0)
		{
			this->y_ = 1;
			this->x_ = 1;
			this->animating_ = true;
		}
	}
}

void ExplosionDrawable::draw()
{
	if (this->animating_ == false)
	{
		this->sprite_.SetX(static_cast<float>(this->posX_));
		this->sprite_.SetY(static_cast<float>(this->posY_));
		this->win_->Draw(this->sprite_);
	}
}


float ExplosionDrawable::getTimeInMs()
{
	float elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void ExplosionDrawable::setPosX(int x)
{
	if (this->width_ != 0)
	{
	 this->width_ = 0;
	 this->posX_ = x;
	}
}

void ExplosionDrawable::setPosY(int y)
{
	if (this->height_ != 0)
	{
		this->height_ = 0;
		this->posY_ = y;
	}
}
