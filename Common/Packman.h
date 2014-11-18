
#ifndef __PACKMAN_H__
#define __PACKMAN_H__

#include <string>

struct DataPacket
{
	struct EndPoint
	{
		std::string host;
		int port;
	};
	EndPoint endpoint;
	std::string data;
};

struct TCPNetPacket
{
	struct Header
	{
		unsigned short len;
		unsigned short request;
	};
	Header header;
	std::string data;
};

struct UDPNetPacket
{
	struct Header
	{
		unsigned short len;
		unsigned short request;
		unsigned int timestamp;
	};
	Header header;
	std::string data;
};

class Packman
{
public:
	static DataPacket* pack(TCPNetPacket const& packet);
	static DataPacket* pack(UDPNetPacket const& packet);
	static TCPNetPacket* unpackTCP(DataPacket const& packet);
	static UDPNetPacket* unpackUDP(DataPacket const& packet);
};


#else

struct DataPacket;
struct TCPNetPacket;
struct UDPNetPacket;
class Packman;

#endif
