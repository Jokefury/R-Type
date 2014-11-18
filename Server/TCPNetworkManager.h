
#pragma once

#include <map>
#include "User.h"
#include "Packman.h"

#if defined(_WIN32) || defined(_WIN64)

#include "WinTCPService.h"
#include "WinSelect.h"
#include "WinServerService.h"

#elif UNIX

#include "UnixTCPService.h"
#include "UnixSelect.h"
#include "UnixServerService.h"

#endif

class TCPNetworkManager
{
  ISelect               *select_;
  IServerService        *acceptor_;
  std::map<int, IService*>	clients_;

public :
  TCPNetworkManager(int port);
  ~TCPNetworkManager();
  IService* acceptService();
  void addService(IService *client);
  void deleteService(int id);
  bool recvFromService(int id, DataPacket const ** ret);
  void sendToService(int id, DataPacket* pckt);
  void wait(unsigned int time);
};
