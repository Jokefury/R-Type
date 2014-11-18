
#ifndef CORE_H
#define CORE_H

#include        <map>
#include        "SafeQueue.h"
#include        "Game.h"
#include        "ThreadPool.h"
#include        "RequestManager.h"
#include        "TCPNetworkManager.h"
#include        "RoomRequestManager.h"

class   Core
{
  TCPNetworkManager                     nm_;
  RoomRequestManager                    *rm_;
  ThreadPool                            gamePool_;
  std::map<int, Room>                   rooms_;
  std::map<int, Game*>                  games_;
  std::map<int, User>                   users_;
  SafeQueue<int>                        dones_;
  std::list<int>                        ready_;
  int                                   maxRoomId;
  
  void  createGames();
  bool  createGame(Room&);
  void  launchGame(int);
  void  roomNotifyPlayer(Room &, int, char, const std::string& userName);

public:
  Core();
  ~Core();
  void                                  run();
  const std::map<int, Room> &           getRooms() const;
  void                                  addUserInRoom(int, int, std::string const&);
  void                                  createRoom(int, std::string const&, int);
  void                                  playerReady(int, int);
  void                                  removeUserFromRoom(int, int);
  void                                  returnRoomList(int);
  void                                  createUser(IService *);
  void                                  playerConnectionReady(int);
};

#else

class   Core;

#endif
