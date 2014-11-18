#pragma once

#include <string>
#include "AEntity.h"
#include "BulletInfos.h"

class AMob : public AEntity
{
private:
  std::string   name_;
  int   points_;
  int   level_;

  AMob(void);
protected:
  AMob(std::string const& name,int id, int points, int dmg, int life, int speed,
       int x, int y, int xHB, int yHB, std::string const& spritePath, std::list<Tile*> & tiles, int level);

public:
  virtual ~AMob(void);
  int getPoints(void) const;
  std::string const& getName(void) const;
  virtual std::list<BulletInfos*> update(int ellapsedTime) = 0;
  int   getLevel() const;
};
