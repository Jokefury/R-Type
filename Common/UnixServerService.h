
#ifndef __UNIX_SERVER_SERVICE_H__
#define __UNIX_SERVER_SERVICE_H__

#include "IServerService.h"

class ServerService : public IServerService
{
private:
  int sock_;
  int port_;

public:
  ServerService(int port);
  virtual ~ServerService();
  virtual IService* acceptService();
  virtual void closeService();
  virtual void const* getRealType() const;
  virtual bool listenServer();
  virtual void wait(); // useless
};

#else

class ServerService;

#endif
