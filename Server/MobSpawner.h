#pragma once

#include        "MobManager.h"
#include        "Tile.h"

enum State
  {
    GENERATING,
    WAITING
  };

class MobSpawner;

typedef void (MobSpawner::*fptrHd)(void);

class   MobSpawner
{
  int                                                   total_;
  MobManager                                            &mm_;
  const std::map<int, std::vector<std::string> >&       levels_;
  int                                                   elapsedTime_;



  std::map<int, int>                                    mobSpawnChances_;

  int													hardness_;
  std::map<int, int >									hardnessMap_;
  std::map<int, fptrHd>									HcMap_;

	void	hdLvl0(void);
	void	hdLvl1(void);
	void	hdLvl2(void);
	void	hdLvl3(void);
	void	hdLvl4(void);
	void	hdLvl5(void);
	void	hdLvl6(void);
	void	hdLvl7(void);
	void	hdLvl8(void);
	void	hdLvl9(void);
	void	hdLvl10(void);
	void	hdLvlHC(void);

  int													totalTime_;
  int                                                   waitDelay_;
  int                                                   waitDuration_;
  int                                                   lastPop_;
  State                                                 state_;
  bool                                                  cloudMode_;
  std::string                                           cloudType_;
  int                                                   cloudNb_;
  int                                                   lastCloudSpawn_;
  int                                                   cloudPos_;

  bool    checkWaiting(std::list<AEntity*>& entities_);
  bool    checkCloudMode(std::list<AEntity*>&);
  void    choseMob(std::list<AEntity*>& entities_, int rnd);

public:
  MobSpawner(MobManager &);
  ~MobSpawner();
  void    Spawn(int, std::list<AEntity*>&);
};
