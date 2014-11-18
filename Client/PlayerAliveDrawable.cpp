#include "PlayerAliveDrawable.h"
#include <iostream>

static const int gIntRecs[4][4] = {
  {67, 3, 99, 15},
  {67, 20, 99, 32},
  {67, 37, 99, 49},
  {67, 54, 99, 66},
};

PlayerAliveDrawable::PlayerAliveDrawable(sf::Image const& img, sf::RenderWindow* ptr, int type)
	: win_(ptr), elapsedTime_(0), alternateMove_(false)
{
	this->state_ = type;
	this->sprite_.SetImage(img);
	this->sprite_.SetSubRect(sf::IntRect(gIntRecs[type][0], gIntRecs[type][1], gIntRecs[type][2], gIntRecs[type][3]));
	this->width_ = this->sprite_.GetSize().x;
	this->height_ = this->sprite_.GetSize().y;
	this->cl_.Reset();
	this->sprite_.SetScale(1.5, 1.5);
}

bool PlayerAliveDrawable::EndingAnim() const
{
	return false;
}
void PlayerAliveDrawable::animate(float angle)
{
		if (angle >= 45 && angle <= 135)
		{
			if (this->alternateMove_ == false && this->elapsedTime_ > 500)
			{
				this->sprite_.SetSubRect(sf::IntRect(gIntRecs[this->state_][0] + 33, 
													gIntRecs[this->state_][1],
													gIntRecs[this->state_][2] + 33,
													gIntRecs[this->state_][3]));
				elapsedTime_ = 0;
				this->alternateMove_ = true;
			}
			else
				this->sprite_.SetSubRect(sf::IntRect(gIntRecs[this->state_][0] + 66 , gIntRecs[this->state_][1], gIntRecs[this->state_][2] + 66, gIntRecs[this->state_][3]));
		}
		else if (angle >= 225 && angle <= 315)
		{

			if (this->alternateMove_ == false && this->elapsedTime_ > 500)
			{
				this->sprite_.SetSubRect(sf::IntRect(gIntRecs[this->state_][0] -33,
													gIntRecs[this->state_][1],
													gIntRecs[this->state_][2] -33,
													gIntRecs[this->state_][3]));
				elapsedTime_ = 0;
				this->alternateMove_ = true;
			}
			else
				this->sprite_.SetSubRect(sf::IntRect(gIntRecs[this->state_][0] -66 , gIntRecs[this->state_][1], gIntRecs[this->state_][2] -66, gIntRecs[this->state_][3]));
		}
		else
		{
			this->elapsedTime_ = 0;
			this->alternateMove_ = false;
			this->sprite_.SetSubRect(sf::IntRect(gIntRecs[this->state_][0] + 33,
												gIntRecs[this->state_][1],
												gIntRecs[this->state_][2] + 33,
												gIntRecs[this->state_][3]));
		}
}

void PlayerAliveDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}


float PlayerAliveDrawable::getTimeInMs()
{
	float elapsed;
	elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void PlayerAliveDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void PlayerAliveDrawable::setPosY(int y)
{
	this->posY_ = y;
}

PlayerAliveDrawable::~PlayerAliveDrawable()
{
}
