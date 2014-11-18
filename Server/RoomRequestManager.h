
#ifndef __RoomRequestManager__
#define __RoomRequestManager__

#include <deque>
#include <map>
#include <list>
#include <string>
#include "Room.h"
#include "Core.h"
#include "Player.h"
#include "RTCP.h"
#include "Packman.h"
#include "Core.h"

class RoomRequestManager
{

  struct ReqRoom
  {
    int id;
    short nb;
    short isRun;
  };

  typedef void (RoomRequestManager::*roomReqFct)(int, TCPNetPacket*);

  Core &core_;
  std::map<RTCP::eRequest, roomReqFct>  ptrF_;

private:

  void  treatmentRoomGetList(int id, TCPNetPacket* packet);
  void  treatmentRoomJoin(int id, TCPNetPacket* packet);
  void  treatmentRoomCreate(int id, TCPNetPacket* packet);
  void  treatmentRoomLeave(int id, TCPNetPacket* packet);
  void  treatmentRoomReady(int id, TCPNetPacket* packet);
  void  treatmentRoomConnectionReady(int id, TCPNetPacket* packet);

public :

  RoomRequestManager(Core &core);
  ~RoomRequestManager();
  void  treatment(int id, DataPacket const * packet);

  DataPacket *  treatmentRoomList(std::map<int, Room> const & rooms);
  DataPacket *  treatmentRoomNotifyJoin(int, short, short, char);
  DataPacket *  treatmentRoomNotifyPlayer(char, std::string const &);
  DataPacket *  treatmentRoomNotifyReady(int);
  DataPacket *  treatmentRoomSendError(RTCP::eRequest);
  DataPacket *  treatmentRoomStartGame(int);

};

#else

class RoomRequestManager;

#endif /* __RoomRequestManager__ */
