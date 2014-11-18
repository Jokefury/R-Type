#pragma once

#include        <string>
#include        "User.h"
#include        "GameRequestManager.h"
#include        "UDPNetworkManager.h"
#include        "IGameClock.h"
#include        "Player.h"
#include        "Tile.h"
#include        "ITask.h"
#include        "BulletManager.h"
#include        "MobManager.h"
#include        "MobSpawner.h"
#include        "SafeQueue.h"

class   Game : public  ITask
{
  std::vector<Player*>  players_;
  std::list<AEntity*>   entities_;
  std::list<Tile*>      tiles_;

  IGameClock            *clock_;
  BulletManager         bm_;
  MobManager            mm_;
  MobSpawner            ms_;
  UDPNetworkManager     nm_;
  GameRequestManager    rm_;
  SafeQueue<int>&       dones_;
  int                   id_;

private:

  Game(const Game &);
  Game & operator=(const Game &);
  void  update();
  void  manageCollisions();
  void  manageMove();
  void  manageLimits();
  bool  gameOver();
  void  respawnPlayers();
  void  manageMobSpawn();

public:
  Game(const std::list<const User *> &, int, int, int, SafeQueue<int>&);
  ~Game();
  void  run();
  virtual void  operator()();
};
