
#include <ctime>
#include <cstring>
#include "EventInput.h"
#include "EventGameEnd.h"
#include "GameRequestManager.h"


GameRequestManager::GameRequestManager(std::list<Obj*>& objs, IGui* gui, ISoundManager* sound, unsigned int idPlayer)
  : objs_(objs), gui_(gui), sound_(sound), idPlayer_(idPlayer), poolEnemys_(10, 5), poolBullets_(20, 5), poolBonus_(5, 2)
{
  this->ptrF_[RTCP::GAME_PLAYER_SPAWN] = &GameRequestManager::treatmentGamePlayerSpawn;
  this->ptrF_[RTCP::GAME_PLAYER_MOVE] = &GameRequestManager::treatmentGamePlayerMove;
  this->ptrF_[RTCP::GAME_PLAYER_DESTROY] = &GameRequestManager::treatmentGamePlayerDestroy;
  this->ptrF_[RTCP::GAME_ENEMY_SPAWN] = &GameRequestManager::treatmentGameEnemySpawn;
  this->ptrF_[RTCP::GAME_ENEMY_MOVE] = &GameRequestManager::treatmentGameEnemyMove;
  this->ptrF_[RTCP::GAME_ENEMY_DESTROY] = &GameRequestManager::treatmentGameEnemyDestroy;
  this->ptrF_[RTCP::GAME_BULLET_SPAWN] = &GameRequestManager::treatmentGameBulletSpawn;
  this->ptrF_[RTCP::GAME_BULLET_MOVE] = &GameRequestManager::treatmentGameBulletMove;
  this->ptrF_[RTCP::GAME_BULLET_DESTROY] = &GameRequestManager::treatmentGameBulletDestroy;
  this->ptrF_[RTCP::GAME_BONUS_SPAWN] = &GameRequestManager::treatmentGameBonusSpawn;
  this->ptrF_[RTCP::GAME_BONUS_PICKED] = &GameRequestManager::treatmentGameBonusPicked;
  this->ptrF_[RTCP::GAME_NOTIFY_END] = &GameRequestManager::treatmentGameNotifyEnd;

  this->ptrEventF_[RTCP::GAME_MOVE] = &GameRequestManager::treatmentGameMove;
  this->ptrEventF_[RTCP::GAME_LAUNCH_SHOT] = &GameRequestManager::treatmentGameLaunchShot;
}

GameRequestManager::~GameRequestManager()
{
}

void GameRequestManager::treatmentGamePlayerSpawn(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (static_cast<int>(tmp->id) >= 0 && tmp->id <= 3)
    {
      Obj* player = this->poolPlayers_.getItem();
      delete player->unsetSprite();
      player->setDead(false);
      player->setState(static_cast<Obj::eState>(Obj::PLAYER_ONE_ALIVE + 2 * tmp->id));
      player->setType(tmp->id);
      player->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
      this->objs_.push_back(player);
      this->players_[tmp->id] = player;
    }
}

void GameRequestManager::treatmentGamePlayerMove(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->players_.find(tmp->id) != this->players_.end())
    this->players_[tmp->id]->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
}

void GameRequestManager::treatmentGamePlayerDestroy(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->players_.find(tmp->id) != this->players_.end())
    {
      this->poolPlayers_.pushItem(this->players_[tmp->id]);
      delete this->players_[tmp->id]->unsetSprite();
      this->players_[tmp->id]->setState(static_cast<Obj::eState>(Obj::PLAYER_ONE_ALIVE + 2 * tmp->id + 1));
      this->players_[tmp->id]->setPos(tmp->posX, tmp->posY, this->players_[tmp->id]->getPos().angle, this->players_[tmp->id]->getPos().speed);
      this->players_.erase(tmp->id);
      this->sound_->playSound(SoundType::DESTROY);
    }
}

void GameRequestManager::treatmentGameEnemySpawn(UDPNetPacket const* packet)
{

  RequestBullet const* tmp = reinterpret_cast<RequestBullet const*>(packet->data.c_str());
  Obj* enemy = this->poolEnemys_.getItem();
  delete enemy->unsetSprite();
  enemy->setDead(false);
  enemy->setState(static_cast<Obj::eState>(Obj::ENEMY_ALIVE_1 + tmp->type % 5 - 1));
	if (tmp->type == 4)
	{	
		this->sound_->stop(SoundType::MUSIC_LVL1);
		this->sound_->playMusic(SoundType::MUSIC_BOSS);		
	}
  enemy->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
  this->objs_.push_back(enemy);
  this->enemys_[tmp->id] = enemy;
}

void GameRequestManager::treatmentGameEnemyMove(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->enemys_.find(tmp->id) != this->enemys_.end())
    this->enemys_[tmp->id]->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
}

void GameRequestManager::treatmentGameEnemyDestroy(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->enemys_.find(tmp->id) != this->enemys_.end())
    {
      this->poolEnemys_.pushItem(this->enemys_[tmp->id]);
	  if (this->enemys_[tmp->id]->getState() == Obj::ENEMY_ALIVE_4)
		{	
			this->sound_->stop(SoundType::MUSIC_BOSS);
			this->sound_->playMusic(SoundType::MUSIC_LVL1);		
		}
      delete this->enemys_[tmp->id]->unsetSprite();
      this->enemys_[tmp->id]->setState(Obj::ENEMY_DEAD);
      this->enemys_[tmp->id]->setPos(tmp->posX, tmp->posY, this->enemys_[tmp->id]->getPos().angle, this->enemys_[tmp->id]->getPos().speed);
      this->enemys_.erase(tmp->id);
    }
}

void GameRequestManager::treatmentGameBulletSpawn(UDPNetPacket const* packet)
{
  RequestBullet const* tmp = reinterpret_cast<RequestBullet const*>(packet->data.c_str());

  if (tmp->type >= 0 && tmp->type < 50)
    {
      Obj* bullet = this->poolBullets_.getItem();
      delete bullet->unsetSprite();
      bullet->setDead(false);
      bullet->setState(static_cast<Obj::eState>(Obj::BULLET_P1_SPAWN + tmp->type / 10));
      bullet->setType(tmp->type % 10);
      bullet->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
      this->objs_.push_back(bullet);
      this->bullets_[tmp->id] = bullet;
      if (tmp->type / 10 == static_cast<int>(this->idPlayer_))
	this->sound_->playSound(SoundType::SHOT);
    }
}

void GameRequestManager::treatmentGameBulletMove(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->bullets_.find(tmp->id) != this->bullets_.end())
    this->bullets_[tmp->id]->setPos(tmp->posX, tmp->posY, tmp->angle, tmp->speed);
}

void GameRequestManager::treatmentGameBulletDestroy(UDPNetPacket const* packet)
{
  RequestPlayer const* tmp = reinterpret_cast<RequestPlayer const*>(packet->data.c_str());

  if (this->bullets_.find(tmp->id) != this->bullets_.end())
    {
      this->poolBullets_.pushItem(this->bullets_[tmp->id]);
      delete this->bullets_[tmp->id]->unsetSprite();
      this->bullets_[tmp->id]->setDead(true);
      this->bullets_[tmp->id]->setState(Obj::BULLET_DESTROY);
      this->bullets_[tmp->id]->setPos(tmp->posX, tmp->posY, this->bullets_[tmp->id]->getPos().angle,
				      this->bullets_[tmp->id]->getPos().speed);
      this->bullets_.erase(tmp->id);
    }
}

void GameRequestManager::treatmentGameBonusSpawn(UDPNetPacket const* packet)
{
  RequestBullet const* tmp = reinterpret_cast<RequestBullet const*>(packet->data.c_str());

  Obj* bonus = this->poolBonus_.getItem();
  delete bonus->unsetSprite();
  bonus->setDead(false);
  bonus->setState(Obj::BONUS_SPAWN);
  bonus->setPos(tmp->posX, tmp->posY, 0, 0);
  this->objs_.push_back(bonus);
  this->bonus_[tmp->id] = bonus;
}

void GameRequestManager::treatmentGameBonusPicked(UDPNetPacket const* packet)
{
  RequestBullet const* tmp = reinterpret_cast<RequestBullet const*>(packet->data.c_str());

  if (this->bonus_.find(tmp->id) != this->bonus_.end())
    {
      this->poolBonus_.pushItem(this->bonus_[tmp->id]);
      delete this->bonus_[tmp->id]->unsetSprite();
      this->bonus_[tmp->id]->setDead(true);
      this->bonus_[tmp->id]->setState(Obj::BONUS_PICKED);
      this->bonus_.erase(tmp->id);
    }
}

void GameRequestManager::treatmentGameNotifyEnd(UDPNetPacket const* packet)
{
  char const* tmp = packet->data.c_str();
  EventGameEnd* event = new EventGameEnd;
  event->setType(RTCP::GAME_NOTIFY_END);
  event->setStatus(tmp[0]);
  int j[4];
  j[0] = *reinterpret_cast<int const*>(&tmp[1]);
  j[1] = *reinterpret_cast<int const*>(&tmp[1 + sizeof(int)]);
  j[2] = *reinterpret_cast<int const*>(&tmp[1 + sizeof(int) * 2]);
  j[3] = *reinterpret_cast<int const*>(&tmp[1 + sizeof(int) * 3]);
  event->setScorePlayer(j[this->idPlayer_]);
  event->setScoreTotal(j[0] + j[1] + j[2] + j[3]);
  this->gui_->setEvent(event);
}

void GameRequestManager::treatmentGameMove(AEvent const* event, UDPNetPacket* packet)
{
  packet->header.len = sizeof(UDPNetPacket::Header) + sizeof(unsigned int) + sizeof(int);
  packet->header.request = RTCP::GAME_MOVE;

  int angle = dynamic_cast<EventInput const*>(event)->getAngle();
  char* tmp = new char[sizeof(unsigned int) + sizeof(int) + 100];
  memcpy(tmp, reinterpret_cast<char*>(&this->idPlayer_), sizeof(unsigned int));
  memcpy(tmp + sizeof(unsigned int), reinterpret_cast<char*>(&angle), sizeof(int));
  packet->data.assign(tmp, sizeof(unsigned int) + sizeof(int));
  delete[] tmp;
}

void GameRequestManager::treatmentGameLaunchShot(AEvent const*, UDPNetPacket* packet)
{
  packet->header.len = sizeof(UDPNetPacket::Header) + sizeof(unsigned int);
  packet->header.request = RTCP::GAME_LAUNCH_SHOT;
  packet->data.assign(reinterpret_cast<char*>(&this->idPlayer_), sizeof(unsigned int));
}

void GameRequestManager::treatmentUDP(DataPacket const* packet)
{
  UDPNetPacket* net = Packman::unpackUDP(*packet);

  delete packet;
  if (this->ptrF_.find(static_cast<RTCP::eRequest>(net->header.request)) != this->ptrF_.end())
    (this->*ptrF_[static_cast<RTCP::eRequest>(net->header.request)])(net);
  delete net;
}

DataPacket* GameRequestManager::treatmentEvent(AEvent const* event)
{
  time_t t;
  UDPNetPacket* packet = new UDPNetPacket;
  DataPacket* ret;

  time(&t);
  packet->header.timestamp = static_cast<unsigned int>(t);
  if (this->ptrEventF_.find(event->getType()) != this->ptrEventF_.end())
    (this->*ptrEventF_[event->getType()])(event, packet);
  delete event;
  ret = Packman::pack(*packet);
  delete packet;
  return ret;
}
