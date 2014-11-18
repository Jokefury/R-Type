
#pragma once

#include <list>
#include "User.h"


#if defined(_WIN32) || defined(_WIN64)

#include "WinUDPService.h"
#include "WinSelect.h"

#elif UNIX

#include "UnixUDPService.h"
#include "UnixSelect.h"

#endif

class UDPNetworkManager
{
  const std::list<const User *>&	clients_;
  ISelect				*select_;
  IService				*socket_;

public :
  UDPNetworkManager(const std::list<const User *>& clients, int port);
  bool recvFromService(int & id, DataPacket const ** ret);
  void wait(int time = Select::NO_TIMEOUT);
  void sendToServices(DataPacket* pckt);
};
