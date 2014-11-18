
#pragma once

#include <deque>
#include <map>
#include <vector>

#include "Player.h"
#include "RTCP.h"

#include "Packman.h"

class GameRequestManager
{

  struct ReqId
  {
    int id_;
  };

  struct ReqMove
  {
    int id_;
    int angle_;
  };

  struct ReqUp
  {
    int id_;
    int posx_;
    int posy_;
    int angle_;
    int speed_;
  };

  struct ReqSpBullet
  {
    int id_;
    int type_;
    int posx_;
    int posy_;
    int angle_;
    int speed_;
  };

  struct ReqSpBonus
  {
    int id_;
    int type_;
    int posx_;
    int posy_;
  };

  struct ReqDestroy
  {
    int id_;
    int posx_;
    int posy_;
  };


  typedef void (GameRequestManager::*gameReqFct)(UDPNetPacket*);

  std::vector<Player*>&                 players_;
  std::map<RTCP::eRequest, gameReqFct>  ptrF_;

private:


  void  treatmentGameMove(UDPNetPacket* packet);
  void  treatmentGameLaunchShot(UDPNetPacket* packet);

  DataPacket *  treatmentSendUpdate(RTCP::eRequest req, int id, AEntity const*p, unsigned int clock);
  DataPacket *  treatmentSendDestroy(RTCP::eRequest req, int id, AEntity const*p, unsigned int clock);

public :

  GameRequestManager(std::vector<Player*>&  players);
  ~GameRequestManager();
  void  treatment(DataPacket const * packet);

  DataPacket *  treatmentGamePlayerSpawn(int id, AEntity const *p, unsigned int clock);
  DataPacket *  treatmentGamePlayerMove(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGamePlayerDestroy(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameEnemySpawn(int id, AEntity const *p, unsigned int clock);
  DataPacket *  treatmentGameEnemyMove(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameEnemyDestroy(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameBulletSpawn(int id, int type, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameBulletMove(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameBulletDestroy(int id, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameBonusSpawn(int id, int type, AEntity const* p, unsigned int clock);
  DataPacket *  treatmentGameBonusPicked(int id, unsigned int clock);
  DataPacket *  treatmentGameNotifyEnd(char status, int p1, int p2, int p3, int p4, unsigned int clock);

};
