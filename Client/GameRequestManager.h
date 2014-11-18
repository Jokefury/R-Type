
#ifndef __GAME_REQUEST_MANAGER_H__
#define __GAME_REQUEST_MANAGER_H__

#include <list>
#include <map>
#include "IGui.h"
#include "Obj.h"
#include "Packman.h"
#include "RTCP.h"
#include "AEvent.h"
#include "PoolManager.h"
#include "ISoundManager.h"

class GameRequestManager
{
private:
	typedef void (GameRequestManager::*reqFunc)(UDPNetPacket const*);
	typedef void (GameRequestManager::*eventFunc)(AEvent const*, UDPNetPacket*);
	struct RequestPlayer
	{
		unsigned int id;
		int posX;
		int posY;
		int angle;
		int speed;
	};

	struct RequestBullet
	{
		unsigned int id;
		int type;
		int posX;
		int posY;
		int angle;
		int speed;
	};

private:
	std::list<Obj*>& objs_;
	IGui* gui_;
	ISoundManager* sound_;
	unsigned int idPlayer_;
	std::map<unsigned int, Obj*> players_;
	std::map<unsigned int, Obj*> enemys_;
	std::map<unsigned int, Obj*> bullets_;
	std::map<unsigned int, Obj*> bonus_;
	PoolManager<Obj> poolPlayers_;
	PoolManager<Obj> poolEnemys_;
	PoolManager<Obj> poolBullets_;
	PoolManager<Obj> poolBonus_;
	std::map<RTCP::eRequest, reqFunc> ptrF_;
	std::map<RTCP::eRequest, eventFunc> ptrEventF_;

private:
	void treatmentGamePlayerSpawn(UDPNetPacket const* packet);
	void treatmentGamePlayerMove(UDPNetPacket const* packet);
	void treatmentGamePlayerDestroy(UDPNetPacket const* packet);
	void treatmentGameEnemySpawn(UDPNetPacket const* packet);
	void treatmentGameEnemyMove(UDPNetPacket const* packet);
	void treatmentGameEnemyDestroy(UDPNetPacket const* packet);
	void treatmentGameBulletSpawn(UDPNetPacket const* packet);
	void treatmentGameBulletMove(UDPNetPacket const* packet);
	void treatmentGameBulletDestroy(UDPNetPacket const* packet);
	void treatmentGameBonusSpawn(UDPNetPacket const* packet);
	void treatmentGameBonusPicked(UDPNetPacket const* packet);
	void treatmentGameNotifyEnd(UDPNetPacket const* packet);

	void treatmentGameMove(AEvent const* event, UDPNetPacket* packet);
	void treatmentGameLaunchShot(AEvent const* event, UDPNetPacket* packet);

public:
  GameRequestManager(std::list<Obj*>& objs, IGui* gui, ISoundManager* sound, unsigned int idPlayer);
	~GameRequestManager();
	void treatmentUDP(DataPacket const* packet);
	DataPacket* treatmentEvent(AEvent const* event);
};

#else

class GameRequestManager;

#endif
