#pragma once

#include <vector>
#include <string>
#include <utility>
#include <list>
#include <map>
#include "Tile.h"
#include "BulletInfos.h"

class Tile;

#define ENV_X           800
#define ENV_Y           600
#define TILE_SIZE       50

enum eTeam {HUMAN, COMP};

class AEntity
{
public:

  enum eEntityType
    {
      MOB, BULLET, PLAYER
    };


private:
  int                   id_;
  int                   dmg_;
  std::pair<int, int>   hitBox_;
  int                   life_;
  int                   lifeMax_;
  std::pair<int, int>   pos_;
  std::pair<int, int>   float_pos_;
  std::string           spritePath_;
  eTeam                 team_;
  std::list<Tile*> &    tiles_;
  int                 moveAngle_;
  bool                  angleUpdated_;
  eEntityType           type_;
  static std::map<int,double>    COS_;
  static std::map<int,double>    SIN_;
  void                  limitPlayer(int & posVar, int pos, bool & angleUp);

protected:
  bool  bulletShot_;
  bool  isMoving_;
  int   speed_;

public:

  AEntity(eEntityType, int id, int dmg, int life, eTeam team, int speed, int x, int y, int xHB, int yHB, std::string const& spritePath, std::list<Tile*> & tiles);
  virtual ~AEntity(void);
  bool                                  collide(AEntity* other);
  eTeam                                 getTeam() const;
  std::pair<int, int>                   getPos() const;
  std::pair<int, int>                   getHitBox() const;
  bool                                  move(int ellapsedTime);
  virtual std::list<BulletInfos*>       update(int) = 0;
  int                                   getDmg() const;
  int                                   getLife() const;
  int                                   takeDmg(int);
  void                                  setMovement(int);
  void					setSpeed(int);
  void                                  setBulletShot(bool);
  bool                                  getBulletShot() const;
  eEntityType                           getType() const;
  int                                   getSpeed() const;
  int                                   getAngle() const;
  int                                   getId() const;
  bool                                  getMoving() const;
  void					setPos(int x, int y);
  void                                  reInit(int x, int y, int moveAngle);
  static void                           initCosSinMap();
};

