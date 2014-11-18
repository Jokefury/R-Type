
#include "RequestManager.h"
#include "EventGeneric.h"
#include "EventRoomList.h"
#include "MenuManager.h"

#include <iostream>

RequestManager::RequestManager(IGui* gui)
	: gui_(gui)
{
	this->ptrF_[RTCP::ROOM_LIST] = &RequestManager::treatmentRoomList;
	this->ptrF_[RTCP::ROOM_NOTIFY_JOIN] = &RequestManager::treatmentRoomNotifyJoin;
	this->ptrF_[RTCP::ROOM_NOTIFY_PLAYER] = &RequestManager::treatmentRoomNotifyPlayer;
	this->ptrF_[RTCP::ROOM_NOTIFY_READY] = &RequestManager::treatmentRoomNotifyReady;
	this->ptrF_[RTCP::ROOM_SEND_RESSOURCES] = &RequestManager::treatmentRoomSendResources;
	this->ptrF_[RTCP::ROOM_START_GAME] = &RequestManager::treatmentRoomStartGame;

	this->ptrEventF_[RTCP::ROOM_GET_LIST] = &RequestManager::treatmentRoomGetList;
	this->ptrEventF_[RTCP::ROOM_JOIN] = &RequestManager::treatmentRoomJoin;
	this->ptrEventF_[RTCP::ROOM_CREATE] = &RequestManager::treatmentRoomCreate;
	this->ptrEventF_[RTCP::ROOM_LEAVE] = &RequestManager::treatmentRoomLeave;
	this->ptrEventF_[RTCP::ROOM_READY] = &RequestManager::treatmentRoomReady;
	this->ptrEventF_[RTCP::ROOM_CONNECTION_READY] = &RequestManager::treatmentRoomConnectionReady;
}

RequestManager::~RequestManager()
{
}

void RequestManager::treatmentRoomList(TCPNetPacket const* packet)
{
	const char* str = packet->data.c_str();
	MenuManager::Room room;
	EventRoomList* list = new EventRoomList;

	list->setType(RTCP::ROOM_LIST);
	for (unsigned int i = 0; i < packet->data.size(); i += sizeof(int) + sizeof(short) + sizeof(char))
	{
		room.id = *reinterpret_cast<int const*>(&str[i]);
		room.nbPlayers = *reinterpret_cast<short const*>(&str[i] + sizeof(int));
		room.launched = str[i + sizeof(int) + sizeof(short)];
		list->addRoom(room);
	}
	this->gui_->setEvent(list);
}

void RequestManager::treatmentRoomNotifyJoin(TCPNetPacket const* packet)
{
	unsigned int const* id = reinterpret_cast<unsigned int const*>(packet->data.c_str());
	short const* portRecv = reinterpret_cast<short const*>(packet->data.c_str() + sizeof(unsigned int));
	short const* portSend = reinterpret_cast<short const*>(packet->data.c_str() + sizeof(unsigned int) + sizeof(short));
	char const* config = packet->data.c_str() + sizeof(unsigned int) + sizeof(short) + sizeof(short);

	EventGeneric* event = new EventGeneric;
	event->setType(RTCP::ROOM_NOTIFY_JOIN);
	event->setInt(*id);
	event->setShort(*portRecv);
	event->setLong(*portSend);
	event->setChar(*config);
	this->gui_->setEvent(event);
}

void RequestManager::treatmentRoomNotifyPlayer(TCPNetPacket const* packet)
{
	EventGeneric* event = new EventGeneric;
	event->setType(RTCP::ROOM_NOTIFY_PLAYER);
	event->setChar(packet->data[0]);
	event->setString(packet->data.substr(1));
	this->gui_->setEvent(event);
}

void RequestManager::treatmentRoomNotifyReady(TCPNetPacket const* packet)
{
	EventGeneric* event = new EventGeneric;
	event->setType(RTCP::ROOM_NOTIFY_READY);
	event->setInt(*reinterpret_cast<unsigned int const*>(packet->data.c_str()));
	this->gui_->setEvent(event);
}

void RequestManager::treatmentRoomSendResources(TCPNetPacket const*)
{
}

void RequestManager::treatmentRoomStartGame(TCPNetPacket const* packet)
{
	EventGeneric* event = new EventGeneric;
	event->setType(RTCP::ROOM_START_GAME);
	event->setChar(packet->data[0]);
	this->gui_->setEvent(event);
}

void RequestManager::treatmentRoomGetList(AEvent const*, TCPNetPacket* packet)
{
	packet->header.len = sizeof(TCPNetPacket::Header);
	packet->header.request = RTCP::ROOM_GET_LIST;
}

void RequestManager::treatmentRoomJoin(AEvent const* event, TCPNetPacket* packet)
{
	EventGeneric const* room = dynamic_cast<EventGeneric const*>(event);

	packet->header.len = sizeof(TCPNetPacket::Header) + sizeof(unsigned int) + room->getString().size();
	packet->header.request = RTCP::ROOM_JOIN;
	unsigned int id = room->getInt();
	packet->data.assign(reinterpret_cast<char*>(&id), sizeof(unsigned int));
	packet->data.append(room->getString());
}

void RequestManager::treatmentRoomCreate(AEvent const* event, TCPNetPacket* packet)
{
	EventGeneric const* room = dynamic_cast<EventGeneric const*>(event);

	packet->header.len = sizeof(TCPNetPacket::Header) + sizeof(char) + room->getString().size();
	packet->header.request = RTCP::ROOM_CREATE;
	char config = room->getChar();
	packet->data.assign(reinterpret_cast<char*>(&config), sizeof(char));
	packet->data.append(room->getString());
}

void RequestManager::treatmentRoomLeave(AEvent const* event, TCPNetPacket* packet)
{
	EventGeneric const* room = dynamic_cast<EventGeneric const*>(event);

	packet->header.len = sizeof(TCPNetPacket::Header) + sizeof(unsigned int) + room->getString().size();
	packet->header.request = RTCP::ROOM_LEAVE;
	unsigned int id = room->getInt();
	packet->data.assign(reinterpret_cast<char*>(&id), sizeof(unsigned int));
	packet->data.append(room->getString());
}

void RequestManager::treatmentRoomReady(AEvent const* event, TCPNetPacket* packet)
{
	EventGeneric const* room = dynamic_cast<EventGeneric const*>(event);

	packet->header.len = sizeof(TCPNetPacket::Header) + sizeof(unsigned int);
	packet->header.request = RTCP::ROOM_READY;
	unsigned int id = room->getInt();
	packet->data.assign(reinterpret_cast<char*>(&id), sizeof(unsigned int));
}

void RequestManager::treatmentRoomConnectionReady(AEvent const*, TCPNetPacket* packet)
{
	packet->header.len = sizeof(TCPNetPacket::Header);
	packet->header.request = RTCP::ROOM_CONNECTION_READY;
}

#include <iostream>
void RequestManager::treatmentTCP(DataPacket const* packet)
{
	TCPNetPacket* net = Packman::unpackTCP(*packet);

	delete packet;
	if (this->ptrF_.find(static_cast<RTCP::eRequest>(net->header.request)) != this->ptrF_.end())
		(this->*ptrF_[static_cast<RTCP::eRequest>(net->header.request)])(net);
	delete net;
}

DataPacket* RequestManager::treatmentEvent(AEvent const* event)
{
	TCPNetPacket* packet = new TCPNetPacket;
	DataPacket* ret;

	if (this->ptrEventF_.find(event->getType()) != this->ptrEventF_.end())
		(this->*ptrEventF_[event->getType()])(event, packet);
	delete event;
	ret = Packman::pack(*packet);
	delete packet;
	return ret;
}
