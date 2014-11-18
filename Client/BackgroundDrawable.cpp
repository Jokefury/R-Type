#include "BackgroundDrawable.h"
#include <iostream>

BackgroundDrawable::BackgroundDrawable(sf::Image const& img, sf::RenderWindow* ptr, int speed)
	: win_(ptr)
{
	this->speed = speed;
	this->sprite_.SetImage(img);
	this->width_ = this->sprite_.GetSize().x;
	this->height_ = this->sprite_.GetSize().y;
	this->cl_.Reset();
}

BackgroundDrawable::~BackgroundDrawable()
{
}

bool BackgroundDrawable::EndingAnim() const
{
	return true;
}

void BackgroundDrawable::animate(float)
{
		this->posX_ -= this->speed ;
		if (sprite_.GetPosition().x < -800)
		{
			this->posX_ = 800;
			sprite_.SetPosition(800, 0);
		}
}

void BackgroundDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}


float BackgroundDrawable::getTimeInMs()
{
	float elapsed;
	elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void BackgroundDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void BackgroundDrawable::setPosY(int y)
{
	this->posY_ = y;
}
