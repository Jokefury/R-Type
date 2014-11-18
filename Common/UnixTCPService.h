
#ifndef __UNIX_TCP_SERVICE_H__
#define __UNIX_TCP_SERVICE_H__

#include "IService.h"

#include <queue>

#define BUFF_SIZE 1024

class TCPService : public IService
{
private:
  static unsigned int lastId;

private:
	unsigned int id_;
	std::string host_;
	int sock_;
	char* buffer_;
	std::queue<DataPacket*> recv_;
	std::queue<DataPacket*> send_;

public:
	TCPService();
	TCPService(int csock, std::string const& host);
	virtual ~TCPService();
	virtual bool closeService();
	virtual bool connectTo(std::string const& ip, int port);
	virtual unsigned int getId() const;
	virtual std::string const& getHost() const;
	virtual void const* getRealType() const;
	virtual DataPacket const* getPacket();
	virtual void pushPacket(DataPacket* packet);
	virtual bool flushRecv();
	virtual void flushSend();
};

#else

class UnixTCPService;

#endif
