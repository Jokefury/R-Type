#pragma once

#include <vector>
#include <list>

#include "AEntity.h"

class AEntity;
class Player;

class Tile
{
private:
  std::list<AEntity*> entities_;
  int xBeg_;
  int xEnd_;

public:
  Tile(int, int);
  ~Tile(void);
  void  collide(std::vector<Player*> &, std::list<AEntity*> &);
  void  pushEntity(AEntity* entity); 
  bool  popEntity(AEntity* entity);
  void	clearTile();
  int getXBeg() const;
  int getXEnd() const;
};
