
#include "AMob.h"
#include "GameRequestManager.h"

GameRequestManager::GameRequestManager(std::vector<Player*>&  players)
  : players_(players)
{
  this->ptrF_[RTCP::GAME_MOVE] = &GameRequestManager::treatmentGameMove;
  this->ptrF_[RTCP::GAME_LAUNCH_SHOT] = &GameRequestManager::treatmentGameLaunchShot;
}

GameRequestManager::~GameRequestManager()
{

}

void    GameRequestManager::treatment(DataPacket const *packet)
{
  UDPNetPacket* net = Packman::unpackUDP(*packet);

  delete packet;
  if (this->ptrF_.find(static_cast<RTCP::eRequest>(net->header.request)) != this->ptrF_.end())
    (this->*ptrF_[static_cast<RTCP::eRequest>(net->header.request)])(net);
}

/*
** Recv Treatment Function
*/

void     GameRequestManager::treatmentGameLaunchShot(UDPNetPacket* packet)
{
  ReqId const* tmp = reinterpret_cast<ReqId const*>(packet->data.c_str());
  
  if (tmp->id_ >= 0 && tmp->id_ <= 3)
    this->players_[tmp->id_]->setBulletShot(true);
}

void     GameRequestManager::treatmentGameMove(UDPNetPacket* packet)
{
  ReqMove const* tmp = reinterpret_cast<ReqMove const*>(packet->data.c_str());

  if (tmp->id_ >= 0 && tmp->id_ <= 3)
    this->players_[tmp->id_]->setMovement(tmp->angle_);
}

/*
** Send General Treatment Functions
*/
DataPacket *    GameRequestManager::treatmentSendUpdate(RTCP::eRequest req, int id, AEntity const* p, unsigned int clock)
{
  UDPNetPacket  tmp;
  ReqUp rp;

  rp.id_ = id;
  rp.posx_ = p->getPos().first;
  rp.posy_ = p->getPos().second;
  rp.angle_ = p->getAngle();
  if (p->getMoving ())
    rp.speed_ = p->getSpeed();
  else
    rp.speed_ = 0;
  tmp.data.assign(reinterpret_cast<char*>(&rp), sizeof(rp));
  tmp.header.len = 8 + sizeof(rp);
  tmp.header.request = req;
  tmp.header.timestamp = clock;

  return (Packman::pack(tmp));
}


DataPacket *    GameRequestManager::treatmentSendDestroy(RTCP::eRequest req, int id, AEntity const* p, unsigned int clock)
{
  UDPNetPacket  tmp;
  ReqDestroy rp;

  rp.id_ = id;
  rp.posx_ = p->getPos().first;
  rp.posy_ = p->getPos().second;
  tmp.data.assign(reinterpret_cast<char*>(&rp), sizeof(rp));
  tmp.header.len = 8 + sizeof(rp);
  tmp.header.request = req;
  tmp.header.timestamp = clock;

  return (Packman::pack(tmp));
}

/*
** Send Specific Treatment Functions
*/
DataPacket* GameRequestManager::treatmentGamePlayerSpawn(int id, AEntity const *p, unsigned int clock)
{
  return this->treatmentSendUpdate(RTCP::GAME_PLAYER_SPAWN, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGamePlayerMove(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendUpdate(RTCP::GAME_PLAYER_MOVE, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGamePlayerDestroy(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendDestroy(RTCP::GAME_PLAYER_DESTROY, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGameEnemySpawn(int id, AEntity const* p, unsigned int clock)
{

	  UDPNetPacket  tmp;
	  ReqSpBullet rp;
	  AMob const* mob;

  rp.id_ = id;
  if ((mob = dynamic_cast<AMob const*>(p)))
	  rp.type_ = ((mob->getLevel() > 4) ? (4) : mob->getLevel());
  else
	  rp.type_ = 0;
  rp.posx_ = p->getPos().first;
  rp.posy_ = p->getPos().second;
  rp.angle_ = p->getAngle();
  if (p->getMoving ())
    rp.speed_ = p->getSpeed();
  else
    rp.speed_ = 0;
  tmp.data.assign(reinterpret_cast<char*>(&rp), sizeof(rp));
  tmp.header.len = 8 + sizeof(rp);
  tmp.header.request = RTCP::GAME_ENEMY_SPAWN;
  tmp.header.timestamp = clock;

  return (Packman::pack(tmp));
}

DataPacket* GameRequestManager::treatmentGameEnemyMove(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendUpdate(RTCP::GAME_ENEMY_MOVE, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGameEnemyDestroy(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendDestroy(RTCP::GAME_ENEMY_DESTROY, id, p, clock);
}


DataPacket* GameRequestManager::treatmentGameBulletSpawn(int, int type, AEntity const* p, unsigned int clock)
{
  UDPNetPacket  tmp;
  ReqSpBullet rp;

  rp.id_ = p->getId();
  rp.type_ = type;
  rp.posx_ = p->getPos().first;
  rp.posy_ = p->getPos().second;
  rp.angle_ = p->getAngle();
  if (p->getMoving ())
    rp.speed_ = p->getSpeed();
  else
    rp.speed_ = 0;
  tmp.data.assign(reinterpret_cast<char*>(&rp), sizeof(rp));
  tmp.header.len = 8 + sizeof(rp);
  tmp.header.request = RTCP::GAME_BULLET_SPAWN;
  tmp.header.timestamp = clock;

  return (Packman::pack(tmp));
}

DataPacket* GameRequestManager::treatmentGameBulletMove(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendUpdate(RTCP::GAME_BULLET_MOVE, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGameBulletDestroy(int id, AEntity const* p, unsigned int clock)
{
  return this->treatmentSendDestroy(RTCP::GAME_BULLET_DESTROY, id, p, clock);
}

DataPacket* GameRequestManager::treatmentGameBonusSpawn(int id, int type, AEntity const*p, unsigned int clock)
{
  UDPNetPacket  tmp;
  ReqSpBonus rp;

  rp.id_ = id;
  rp.type_ = type;
  rp.posx_ = p->getPos().first;
  rp.posy_ = p->getPos().second;
  tmp.data.assign(reinterpret_cast<char*>(&rp), sizeof(rp));
  tmp.header.len = 8 + sizeof(rp);
  tmp.header.request = RTCP::GAME_BONUS_SPAWN;
  tmp.header.timestamp = clock;

  return (Packman::pack(tmp));
}

DataPacket* GameRequestManager::treatmentGameBonusPicked(int id, unsigned int clock)
{
  UDPNetPacket  tmp;

  tmp.data.assign(reinterpret_cast<char*>(&id), sizeof(id));
  tmp.header.len = 8 + sizeof(id);
  tmp.header.request = RTCP::GAME_BONUS_PICKED;
  tmp.header.timestamp = clock;
  return (Packman::pack(tmp));
}

DataPacket* GameRequestManager::treatmentGameNotifyEnd(char status, int p1, int p2, int p3, int p4, unsigned int clock)
{
	UDPNetPacket tmp;

	tmp.data.assign(reinterpret_cast<char*>(&status), sizeof(status));
	tmp.data.append(reinterpret_cast<char*>(&p1), sizeof(p1));
	tmp.data.append(reinterpret_cast<char*>(&p2), sizeof(p2));
	tmp.data.append(reinterpret_cast<char*>(&p3), sizeof(p3));
	tmp.data.append(reinterpret_cast<char*>(&p4), sizeof(p4));
	tmp.header.len = 8 + (sizeof(int) * 4) + sizeof(char);
	tmp.header.request = RTCP::GAME_NOTIFY_END;
	tmp.header.timestamp = clock;
	return (Packman::pack(tmp));
}
