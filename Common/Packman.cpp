
#include "Packman.h"
#include <string.h>

DataPacket* Packman::pack(TCPNetPacket const& packet)
{
	char* tmp = new char[4 + packet.data.size()];

	memcpy(tmp, reinterpret_cast<const void*>(&packet.header.len), sizeof(unsigned short));
	memcpy(tmp + 2, reinterpret_cast<const void*>(&packet.header.request), sizeof(unsigned short));
	memcpy(tmp + 4, packet.data.c_str(), packet.data.size());
	DataPacket* ret = new DataPacket;
	ret->data.assign(tmp, 4 + packet.data.size());
	delete[] tmp;
	return ret;
}

DataPacket* Packman::pack(UDPNetPacket const& packet)
{
	char* tmp = new char[8 + packet.data.size()];

	memcpy(tmp, reinterpret_cast<const void*>(&packet.header.len), sizeof(unsigned short));
	memcpy(tmp + 2, reinterpret_cast<const void*>(&packet.header.request), sizeof(unsigned short));
	memcpy(tmp + 4, reinterpret_cast<const void*>(&packet.header.timestamp), sizeof(unsigned int));
	memcpy(tmp + 8, packet.data.c_str(), packet.data.size());
	DataPacket* ret = new DataPacket;
	ret->data.assign(tmp, 8 + packet.data.size());
	delete[] tmp;
	return ret;
}

TCPNetPacket* Packman::unpackTCP(DataPacket const& packet)
{
	TCPNetPacket* ret = new TCPNetPacket;

	memcpy(&ret->header, packet.data.data(), sizeof(TCPNetPacket::Header));
	char* tmp = new char[packet.data.size() - sizeof(TCPNetPacket::Header)];
	memcpy(tmp, packet.data.c_str() + sizeof(TCPNetPacket::Header), packet.data.size() - sizeof(TCPNetPacket::Header));
	ret->data.assign(tmp, packet.data.size() - sizeof(TCPNetPacket::Header));
	delete[] tmp;
	return ret;
}

UDPNetPacket* Packman::unpackUDP(DataPacket const& packet)
{
	UDPNetPacket* ret = new UDPNetPacket;

	memcpy(&ret->header, packet.data.data(), sizeof(UDPNetPacket::Header));
	char* tmp = new char[packet.data.size() - sizeof(UDPNetPacket::Header)];
	memcpy(tmp, packet.data.c_str() + sizeof(UDPNetPacket::Header), packet.data.size() - sizeof(UDPNetPacket::Header));
	ret->data.assign(tmp, packet.data.size() - sizeof(UDPNetPacket::Header));
	delete[] tmp;
	return ret;
}
