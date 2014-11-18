#include "EnemyDrawable.h"

EnemyDrawable::EnemyDrawable(sf::Image const& img, sf::RenderWindow* ptr)
	: win_(ptr), elapsedTime_(0)
{

	this->sprite_.SetImage(img);
	this->sprite_.SetSubRect(sf::IntRect(5,6,26,30));
	this->width_ = static_cast<float>(img.GetWidth());
	this->height_ = static_cast<float>(img.GetHeight());
	this->cl_.Reset();
	this->sprite_.SetScale(1.5, 1.5);
}

EnemyDrawable::~EnemyDrawable()
{
}

bool EnemyDrawable::EndingAnim() const
{
	return false;
}

void EnemyDrawable::animate(float)
{
	static int i = 8;
	
	int save = (int)((this->width_ - i * (width_ / 16) ));
	sprite_.SetSubRect(sf::IntRect(save - (static_cast<int>(this->width_) / 16),
			0, save, static_cast<int>(this->height_)));
	if (this->elapsedTime_ >= 300)
	{
		this->elapsedTime_ = 0;
		i++;
	}	 
	if (i >= 16 )
		i = 8;
}

void EnemyDrawable::draw()
{
	this->sprite_.SetX(static_cast<float>(this->posX_));
	this->sprite_.SetY(static_cast<float>(this->posY_));
	this->win_->Draw(this->sprite_);
}


float EnemyDrawable::getTimeInMs()
{
	float elapsed = this->cl_.GetElapsedTime() * 1000;
	this->elapsedTime_ += elapsed;
	this->cl_.Reset();
	return elapsed;
}

void EnemyDrawable::setPosX(int x)
{
	this->posX_ = x;
}

void EnemyDrawable::setPosY(int y)
{
	this->posY_ = y;
}
