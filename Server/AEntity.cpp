#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <map>
#include "AEntity.h"
#include "Player.h"

std::map<int,double> AEntity::COS_;
std::map<int,double> AEntity::SIN_;

void                                                    AEntity::initCosSinMap()
{
  COS_[0] = 1.0;
  COS_[15] = 0.965925826;
  COS_[30] = 0.866025404;
  COS_[45] = 0.707106781;
  COS_[60] = 0.5;
  COS_[75] = 0.258819045;
  COS_[90] = 0;
  COS_[105] = -0.258819045;
  COS_[120] = -0.5;
  COS_[135] = -0.707106781;
  COS_[150] = -0.866025404;
  COS_[165] = -0.965925826;
  COS_[180] = -1;
  COS_[195] = -0.965925826;
  COS_[210] = -0.866025404;
  COS_[225] = -0.707106781;
  COS_[240] = -0.5;
  COS_[255] = -0.258819045;
  COS_[270] = 0;
  COS_[285] = 0.258819045;
  COS_[300] = 0.5;
  COS_[315] = 0.707106781;
  COS_[330] = 0.866025404;
  COS_[345] = 0.965925826;
  COS_[-1] = 0;

  SIN_[0] = 0;
  SIN_[15] = 0.258819045;
  SIN_[30] = 0.5;
  SIN_[45] = 0.707106781;
  SIN_[60] = 0.866025404;
  SIN_[75] = 0.965925826;
  SIN_[90] = 1;
  SIN_[105] = 0.965925826;
  SIN_[120] = 0.866025404;
  SIN_[135] = 0.707106781;
  SIN_[150] = 0.5;
  SIN_[165] = 0.258819045;
  SIN_[180] = 0;
  SIN_[195] = -0.258819045;
  SIN_[210] = -0.5;
  SIN_[225] = -0.707106781;
  SIN_[240] = -0.866025404;
  SIN_[255] = -0.965925826;
  SIN_[270] = -1;
  SIN_[285] = -0.965925826;
  SIN_[300] = -0.866025404;
  SIN_[315] = -0.707106781;
  SIN_[330] = -0.5;
  SIN_[345] = -0.258819045;
  SIN_[-1] = 0;
}

AEntity::AEntity(eEntityType type, int id, int dmg, int life, eTeam team,
		 int speed, int x, int y, int xHB, int yHB,
		 std::string const& spritePath, std::list<Tile*> & tiles)
  : id_ (id), tiles_ (tiles), angleUpdated_ (false), type_ (type), isMoving_ (true)
{
  std::list <Tile *>::iterator  it;
  int   ex1;
  int   ex2;

  this->bulletShot_ = false;
  this->dmg_ = dmg;
  this->lifeMax_ = life;
  this->life_ = life;
  this->team_ = team;
  this->moveAngle_ = 0;
  this->speed_ = speed;
  this->tiles_ = tiles;
  this->spritePath_ = spritePath;
  this->hitBox_.first = xHB;
  this->hitBox_.second = yHB;
  this->pos_.first = x;
  this->pos_.second = y;
  this->float_pos_.first = x;
  this->float_pos_.second = y;

  ex1 = this->pos_.first;
  ex2 = this->pos_.first + this->hitBox_.first;
  for (it = this->tiles_.begin(); it != this->tiles_.end(); ++it)
    {
      int       tx1 = (*it)->getXBeg();
      int       tx2 = (*it)->getXEnd();
      (*it)->popEntity(this);
      if ((ex1 > tx1 && ex1 < tx2) || (ex2 > tx1 && ex2 < tx2) ||
          (tx1 > ex1 && tx2 < ex2))
        (*it)->pushEntity(this);
    }
}


AEntity::~AEntity(void)
{
}

bool    AEntity::collide(AEntity* o)
{
  int   x1;
  int   y1;
  int   x2;
  int   y2;

  if (this->getType() == AEntity::PLAYER)
	  if (dynamic_cast<Player*>(this)->getRespawn())
		  return false;
   if (o->getType() == AEntity::PLAYER)
	  if (dynamic_cast<Player*>(o)->getRespawn())
		  return false;
  x1 = this->pos_.first;
  y1 = this->pos_.second;
  x2 = x1 + this->hitBox_.first;
  y2 = y1 + this->hitBox_.second;
  if (((x1 >= o->pos_.first  && x1 <= (o->pos_.first  + o->hitBox_.first)) &&
       (y1 >= o->pos_.second && y1 <= (o->pos_.second + o->hitBox_.second))) ||
      ((x2 >= o->pos_.first  && x2 <= (o->pos_.first  + o->hitBox_.first)) &&
       (y1 >= o->pos_.second && y1 <= (o->pos_.second + o->hitBox_.second))) ||
      ((x1 >= o->pos_.first  && x1 <= (o->pos_.first  + o->hitBox_.first)) &&
       (y2 >= o->pos_.second && y2 <= (o->pos_.second + o->hitBox_.second))) ||
      ((x2 >= o->pos_.first  && x2 <= (o->pos_.first  + o->hitBox_.first)) &&
       (y2 >= o->pos_.second && y2 <= (o->pos_.second + o->hitBox_.second))))
    return (true);
  return (false);
}

eTeam             AEntity::getTeam() const
{
  return (this->team_);
}

std::pair<int, int>                   AEntity::getPos() const
{
  return (this->pos_);
}

std::pair<int, int>                   AEntity::getHitBox() const
{
  return (this->hitBox_);
}

void    AEntity::limitPlayer(int & posVar, int pos, bool & angleUp)
{
  posVar = pos;
  this->isMoving_ = false;
  angleUp = true;
}

bool    AEntity::move(int ellapsedTime)
{
  bool  angleUp = this->angleUpdated_;
  std::list <Tile *>::iterator  it;
  int   ex1;
  int   ex2;

  this->angleUpdated_ = false;
  if (this->life_ <= 0)
    return angleUp;
  if (!this->isMoving_)
    {
      ex1 = this->pos_.first;
      ex2 = this->pos_.first + this->hitBox_.first;

      for (it = this->tiles_.begin(); it != this->tiles_.end(); ++it)
        {
          int       tx1 = (*it)->getXBeg();
          int       tx2 = (*it)->getXEnd();
          if ((ex1 > tx1 && ex1 < tx2) || (ex2 > tx1 && ex2 < tx2) ||
              (tx1 > ex1 && tx2 < ex2))
            (*it)->pushEntity(this);
        }
      return angleUp;
    }

  this->float_pos_.first += static_cast<int>(COS_[this->moveAngle_] * this->speed_ * ellapsedTime / 20);
  this->float_pos_.second -= static_cast<int>(SIN_[this->moveAngle_] * this->speed_ * ellapsedTime / 20);

  if (this->type_ == AEntity::PLAYER)
    {
      if (this->float_pos_.first < 5.0)
        limitPlayer(this->float_pos_.first, 5, angleUp);
      if (this->float_pos_.first > ENV_X - 50)
        limitPlayer(this->float_pos_.first, ENV_X - 50, angleUp);
      if (this->float_pos_.second < 5)
        limitPlayer(this->float_pos_.second, 5, angleUp);
      if (this->float_pos_.second > ENV_Y - 20)
        limitPlayer(this->float_pos_.second,  ENV_Y -20, angleUp);
    }

  this->pos_.first = float_pos_.first;
  this->pos_.second = float_pos_.second;


  ex1 = this->pos_.first;
  ex2 = this->pos_.first + this->hitBox_.first;

  for (it = this->tiles_.begin(); it != this->tiles_.end(); ++it)
    {
      int       tx1 = (*it)->getXBeg();
      int       tx2 = (*it)->getXEnd();
      if ((ex1 > tx1 && ex1 < tx2) || (ex2 > tx1 && ex2 < tx2) ||
          (tx1 > ex1 && tx2 < ex2))
        (*it)->pushEntity(this);
    }
  return angleUp;
}

void    AEntity::setBulletShot(bool shot)
{
  this->bulletShot_ = shot;
}

bool    AEntity::getBulletShot() const
{
  return (this->bulletShot_);
}


int     AEntity::getDmg() const
{
  return (this->dmg_);
}

int     AEntity::getLife() const
{
  return (this->life_);
}

int     AEntity::takeDmg(int dmg)
{
  this->life_ -= dmg;
  return (this->life_);
}

void    AEntity::setMovement(int angle)
{
  isMoving_ = (angle != -1);
  angleUpdated_ = true;
  if (moveAngle_ == angle)
    return;
  moveAngle_ = angle;
}

void	AEntity::setSpeed(int speed)
{
	this->speed_ = speed;
}

AEntity::eEntityType     AEntity::getType() const
{
  return type_;
}

int     AEntity::getSpeed() const
{
  return speed_;
}

int     AEntity::getAngle() const
{
  return moveAngle_;
}

int     AEntity::getId() const
{
  return (this->id_);
}

bool    AEntity::getMoving() const
{
  return isMoving_;
}

void	AEntity::setPos(int x, int y)
{
	this->pos_.first = x;
	this->pos_.second = y;
}

void    AEntity::reInit(int x, int y, int moveAngle)
{
  this->life_ = this->lifeMax_;
  this->pos_.first = x;
  this->pos_.second = y;
  this->float_pos_.first = x;
  this->float_pos_.second = y;
  this->moveAngle_ = moveAngle;
}
