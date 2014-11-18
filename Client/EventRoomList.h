
#pragma once

#include "AEvent.h"
#include "MenuManager.h"
#include <vector>

class EventRoomList : public AEvent
{
private:
	std::vector<MenuManager::Room> rooms_;

public:
	EventRoomList();
	virtual ~EventRoomList();
	std::vector<MenuManager::Room> const& getListRoom() const;
	void addRoom(MenuManager::Room const& room);
	void resetListRoom();

};