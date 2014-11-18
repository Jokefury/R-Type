
#pragma once

#include "AEvent.h"
#include "Packman.h"
#include "RTCP.h"
#include "IGui.h"
#include <map>

class RequestManager
{
private:
	typedef void (RequestManager::*reqFunc)(TCPNetPacket const* packet);
	typedef void (RequestManager::*eventFunc)(AEvent const* event, TCPNetPacket* packet);

private:
	std::map<RTCP::eRequest, reqFunc> ptrF_;
	std::map<RTCP::eRequest, eventFunc> ptrEventF_;
	IGui* gui_;

private:
	void treatmentRoomList(TCPNetPacket const* packet);
	void treatmentRoomNotifyJoin(TCPNetPacket const* packet);
	void treatmentRoomNotifyPlayer(TCPNetPacket const* packet);
	void treatmentRoomNotifyReady(TCPNetPacket const* packet);
	void treatmentRoomSendResources(TCPNetPacket const* packet);
	void treatmentRoomStartGame(TCPNetPacket const* packet);

	void treatmentRoomGetList(AEvent const* event, TCPNetPacket* packet);
	void treatmentRoomJoin(AEvent const* event, TCPNetPacket* packet);
	void treatmentRoomCreate(AEvent const* event, TCPNetPacket* packet);
	void treatmentRoomLeave(AEvent const* event, TCPNetPacket* packet);
	void treatmentRoomReady(AEvent const* event, TCPNetPacket* packet);
	void treatmentRoomConnectionReady(AEvent const* event, TCPNetPacket* packet);

public:
	RequestManager(IGui* gui);
	~RequestManager();
	void treatmentTCP(DataPacket const* packet);
	DataPacket* treatmentEvent(AEvent const* event);
};