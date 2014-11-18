#pragma once

#include <string>
#include "AEntity.h"

class ABullet : public AEntity
{
private:
  std::string   name_;
  int		idOwner_;
  int		BType_;

public:
  ABullet(std::string const& name, int BType, int id, int dmg, int life, eTeam team, int speed, int x, int y, int xHB, int yHB, std::string const& spritePath, std::list<Tile*>& tiles);
  virtual ~ABullet(void);
  std::string const& getName() const;
  int getIdOwner() const;
  void setIdOwner(int id);
  void setBType(int);
  int getBType() const;
  virtual std::list<BulletInfos*> update(int ellapsedTime) = 0;
};
