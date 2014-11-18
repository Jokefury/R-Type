
#include "RoomRequestManager.h"
#include <iostream>

RoomRequestManager::RoomRequestManager(Core &core)
  : core_(core)
{
  this->ptrF_[RTCP::ROOM_GET_LIST] = &RoomRequestManager::treatmentRoomGetList;
  this->ptrF_[RTCP::ROOM_JOIN] = &RoomRequestManager::treatmentRoomJoin;
  this->ptrF_[RTCP::ROOM_CREATE] = &RoomRequestManager::treatmentRoomCreate;
  this->ptrF_[RTCP::ROOM_LEAVE] = &RoomRequestManager::treatmentRoomLeave;
  this->ptrF_[RTCP::ROOM_READY] = &RoomRequestManager::treatmentRoomReady;
  this->ptrF_[RTCP::ROOM_CONNECTION_READY] = &RoomRequestManager::treatmentRoomConnectionReady;
}

RoomRequestManager::~RoomRequestManager()
{
}

void    RoomRequestManager::treatment(int id, DataPacket const * packet)
{
  TCPNetPacket* net = Packman::unpackTCP(*packet);

  delete packet;
  if (this->ptrF_.find(static_cast<RTCP::eRequest>(net->header.request)) != this->ptrF_.end())
    (this->*ptrF_[static_cast<RTCP::eRequest>(net->header.request)])(id, net);
}

/*
** Treatment recv function
*/

void    RoomRequestManager::treatmentRoomGetList(int id, TCPNetPacket*)
{
  core_.returnRoomList (id);
}

void    RoomRequestManager::treatmentRoomJoin(int id, TCPNetPacket* packet)
{
  int const * rid = reinterpret_cast<int const *>(packet->data.c_str());
  char const * data = reinterpret_cast<char const *>(packet->data.c_str() + 4);

  std::string name(data, packet->header.len - (sizeof(packet->header) + 4));
  core_.addUserInRoom (id, *rid, name);
}

void    RoomRequestManager::treatmentRoomCreate(int id, TCPNetPacket* packet)
{
  char const* conf = reinterpret_cast<char const*>(packet->data.c_str());
  char const* data = reinterpret_cast<char const*>(packet->data.c_str() + 1);

  std::string name(data, packet->header.len - (sizeof(packet->header) + 1));
  core_.createRoom (id, name, *conf);
}

void    RoomRequestManager::treatmentRoomLeave(int id, TCPNetPacket* packet)
{
  int const * rid = reinterpret_cast<int const *>(packet->data.c_str());
  char const * data = reinterpret_cast<char const *>(packet->data.c_str() + 4);

  std::string name(data, packet->header.len - (sizeof(packet->header) + 4));
  core_.removeUserFromRoom (id, *rid);
}

void    RoomRequestManager::treatmentRoomReady(int id, TCPNetPacket* packet)
{
  int const * id_r = reinterpret_cast<int const *>(packet->data.c_str());

  core_.playerReady (id, *id_r);
}

void    RoomRequestManager::treatmentRoomConnectionReady(int id, TCPNetPacket*)
{
  core_.playerConnectionReady (id);
}

DataPacket *    RoomRequestManager::treatmentRoomNotifyJoin
(int rid, short sendPort, short recvPort, char conf)
{
  TCPNetPacket  tmp;

  tmp.data.assign(reinterpret_cast<char*>(&rid), sizeof(int));
  tmp.data.append(reinterpret_cast<char*>(&sendPort), sizeof(short));
  tmp.data.append(reinterpret_cast<char*>(&recvPort), sizeof(short));
  tmp.data.append(reinterpret_cast<char*>(&conf), sizeof(char));

  tmp.header.len = 13;
  tmp.header.request = RTCP::ROOM_NOTIFY_JOIN;

  return (Packman::pack(tmp));
}

DataPacket *    RoomRequestManager::treatmentRoomSendError
(RTCP::eRequest code)
{
  TCPNetPacket  tmp;

  tmp.data.clear();
  tmp.header.len = 5;
  tmp.header.request = code;

  return (Packman::pack(tmp));
}

DataPacket *    RoomRequestManager::treatmentRoomNotifyPlayer
(char isRm, std::string const & name)
{
  TCPNetPacket  tmp;

  tmp.data.assign(reinterpret_cast<char*>(&isRm), sizeof(isRm));
  tmp.data.append(name.data(), name.size());
  tmp.header.len = 5 + name.size();
  tmp.header.request = RTCP::ROOM_NOTIFY_PLAYER;

  return (Packman::pack(tmp));
}

#include <iostream>

DataPacket *    RoomRequestManager::treatmentRoomNotifyReady
(int nbClients)
{
  TCPNetPacket  tmp;

  tmp.data.assign(reinterpret_cast<char*>(&nbClients), sizeof(nbClients));
  tmp.header.len = 8;
  tmp.header.request = RTCP::ROOM_NOTIFY_READY;
  return (Packman::pack(tmp));
}

DataPacket *    RoomRequestManager::treatmentRoomStartGame
(int pid)
{
  TCPNetPacket  tmp;

  tmp.data.assign(reinterpret_cast<char*>(&pid), sizeof(pid));
  tmp.header.len = 8;
  tmp.header.request = RTCP::ROOM_START_GAME;


  return (Packman::pack(tmp));
}

DataPacket *    RoomRequestManager::treatmentRoomList(std::map<int, Room> const & rooms)
{
  TCPNetPacket  tmp;
  ReqRoom       req;

  if (!rooms.empty())
    {
      std::map<int, Room>::const_iterator it = rooms.begin();
      req.id = it->second.getId();
      req.nb = it->second.getNbPlayers();
      if (it->second.isRunning())
        req.isRun = 1;
      else
        req.isRun = 0;
      tmp.data.assign(reinterpret_cast<char*>(&(req.id)), sizeof(int));
      tmp.data.append(reinterpret_cast<char*>(&(req.nb)), sizeof(short));
      tmp.data.append(reinterpret_cast<char*>(&(req.isRun)), sizeof(char));
      ++it;
      for (; it != rooms.end(); ++it)
        {
          req.id = it->second.getId();
          req.nb = it->second.getNbPlayers();
          if (it->second.isRunning())
            req.isRun = 1;
          else
            req.isRun = 0;
          tmp.data.append(reinterpret_cast<char*>(&(req.id)), sizeof(int));
          tmp.data.append(reinterpret_cast<char*>(&(req.nb)), sizeof(short));
          tmp.data.append(reinterpret_cast<char*>(&(req.isRun)), sizeof(char));
        }
      tmp.header.len = 4 + 7 * rooms.size();
    }
  else
    {
      tmp.data.clear();
      tmp.header.len = 4;
    }
  tmp.header.request = RTCP::ROOM_LIST;

  return (Packman::pack(tmp));
}
