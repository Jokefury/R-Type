#define _USE_MATH_DEFINES

#include <math.h>
#include "Obj.h"


Obj::Obj()
  : type_(0), sprite_(0), isDead_(false)
{
}

Obj::~Obj()
{
}

void Obj::setDead(bool st)
{
	this->isDead_ = st;
}

bool Obj::isDead() const
{
	return this->isDead_;
}

void Obj::setPos(Obj::Position const& pos)
{
  this->pos_ = pos;
}

void Obj::setPos(unsigned int posX, unsigned int posY, int angle, int speed)
{
  this->pos_.posX = static_cast<float>(posX);
  this->pos_.posY = static_cast<float>(posY);
  this->pos_.angle = angle;
  this->pos_.speed = speed;
}

void Obj::setState(Obj::eState state)
{
  this->state_ = state;
}

void Obj::setType(int type)
{
  this->type_ = type;
}

void Obj::setSprite(IDrawable* sprite)
{
  this->sprite_ = sprite;
}

IDrawable* Obj::unsetSprite()
{
  IDrawable* tmp = this->sprite_;
  this->sprite_ = 0;
  return tmp;
}

Obj::Position const& Obj::getPos() const
{
  return this->pos_;
}

Obj::eState Obj::getState() const
{
  return this->state_;
}

int	Obj::getType() const
{
  return this->type_;
}

bool	Obj::isSetSprite() const
{
  return (this->sprite_ != 0);
}

float   Obj::myRound(float val)
{
  return floor (val * 1000) / 1000;
}

void Obj::draw()
{
  if (this->sprite_)
    this->sprite_->draw();
}

void Obj::update()
{
  float elapsedtime =  this->sprite_->getTimeInMs();
  float rad = static_cast<float>(M_PI / 180.0f * pos_.angle);
  pos_.posX += (pos_.speed * elapsedtime  / 20) * Obj::myRound(cos(rad));
  pos_.posY -= (pos_.speed * elapsedtime / 20) * Obj::myRound(sin(rad));
  this->sprite_->setPosX(static_cast<int>(pos_.posX));
  this->sprite_->setPosY(static_cast<int>(pos_.posY));
  if (this->sprite_)
  {
    this->sprite_->animate(static_cast<float>(this->pos_.angle));
    this->isDead_ = this->sprite_->EndingAnim();
  }
}
