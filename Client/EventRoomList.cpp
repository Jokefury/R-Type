
#include "EventRoomList.h"

EventRoomList::EventRoomList()
{
}

EventRoomList::~EventRoomList()
{
}

std::vector<MenuManager::Room> const& EventRoomList::getListRoom() const
{
	return this->rooms_;
}

void EventRoomList::addRoom(MenuManager::Room const& room)
{
	this->rooms_.push_back(room);
}

void EventRoomList::resetListRoom()
{
	this->rooms_.clear();
}