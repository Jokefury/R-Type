#pragma once

#include <string>
#include <map>
#include <list>
#include "AEntity.h"

typedef void (Player::*fptrLvl)(std::list<BulletInfos*>&);

class Player : public AEntity
{
private:
  std::string   name_;
  int		points_;
  int		lastShot_;
  int		deathTime_;
  bool		respawn_;
  int		lvl_;
  int		spaceShip_;
  std::map<int, int>	XpMap_;
  std::map<int, fptrLvl>	fireMap_;
  int socketId_;

private:
  void	fireLvl1(std::list<BulletInfos*>& bullets);
  void	fireLvl2(std::list<BulletInfos*>& bullets);
  void	fireLvl3(std::list<BulletInfos*>& bullets);
  void	fireLvl4(std::list<BulletInfos*>& bullets);
  void	fireLvl5(std::list<BulletInfos*>& bullets);
  void	fireLvl6(std::list<BulletInfos*>& bullets);
  void	fireLvl7(std::list<BulletInfos*>& bullets);
  
public:
  Player(std::string const&, int, int, int, std::string const&, std::list<Tile*> &, int);
  virtual ~Player(void);
  std::string const&            getName() const;
  int							getSocketId() const;
  virtual std::list<BulletInfos*>       update(int);
  int				addPoints(int);
  int				getPoints() const;
  void				setPoints(int);
  int				getSpaceShip() const;
  void				setRespawn(bool);
  bool				getRespawn() const;
  void				setSpaceShip(int spaceShip);
  int				addSpaceShip(int spaceShip);
  void				setDeathTime(int);
  int				getDeathTime() const;
};
