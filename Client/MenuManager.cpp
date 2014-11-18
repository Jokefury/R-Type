#include "MenuManager.h"
#include "LoadingMenu.h"
#include "ListRoomMenu.h"
#include "RoomMenu.h"
#include "MainMenu.h"
#include "ErrorMenu.h"
#include "EventRoomList.h"
#include "EventGeneric.h"
#include "PauseMenu.h"
#include "ScoresMenu.h"
#include "EventGameEnd.h"

#include <iostream>

MenuManager::MenuManager(sf::RenderWindow *win, std::string const& username)
	:	window_(win),
		current_(Menus::LOADING),
		username_(username),
		event_(0)
{
	this->menus_[Menus::LOADING] = new LoadingMenu(this->window_);
	this->menus_[Menus::LOADING]->init();
	this->ptrF_[RTCP::ROOM_LIST] = &MenuManager::treatmentEventListRoom;
	this->ptrF_[RTCP::ROOM_NOTIFY_JOIN] = &MenuManager::treatmentEventNotifyJoin;
	this->ptrF_[RTCP::ROOM_NOTIFY_PLAYER] = &MenuManager::treatmentEventNotifyPlayer;
	this->ptrF_[RTCP::ROOM_NOTIFY_READY] = &MenuManager::treatmentEventNotifyReady;
	this->ptrF_[RTCP::ROOM_START_GAME] = &MenuManager::treatmentEventStartGame;
	this->ptrF_[RTCP::GAME_NOTIFY_END] = &MenuManager::treatmentEventNotifyGameEnd;
	this->ptrF_[RTCP::NETWORK_CONNECTED] = &MenuManager::treatmentEventNetworkConnected;
	this->ptrF_[RTCP::NETWORK_DISCONNECTED] = &MenuManager::treatmentEventNetworkDisconnected;
	this->ptrF_[RTCP::GAME_PAUSE] = &MenuManager::treatmentEventGamePause;
}

MenuManager::~MenuManager()
{
}

void	MenuManager::init()
{
	this->menus_[Menus::MAIN] = new MainMenu(this->window_, this->username_);
	this->menus_[Menus::MAIN]->init();
	this->menus_[Menus::LIST_ROOM] = new ListRoomMenu(this->window_, this->username_);
	this->menus_[Menus::LIST_ROOM]->init();
	this->menus_[Menus::ROOM] = new RoomMenu(this->window_, this->room_, this->username_);
	this->menus_[Menus::ROOM]->init();
	this->menus_[Menus::ERROR_NETWORK] = new ErrorMenu(this->window_);
	this->menus_[Menus::ERROR_NETWORK]->init();
	this->menus_[Menus::PAUSE] = new PauseMenu(this->window_);
	this->menus_[Menus::PAUSE]->init();
	this->menus_[Menus::SCORES] = new ScoresMenu(this->window_);
	this->menus_[Menus::SCORES]->init();
	this->current_ = Menus::MAIN;
	this->room_.nbPlayersReady = 0;
	this->room_.nbPlayers = 0;
}

void	MenuManager::update()
{
	this->current_ = this->menus_[this->current_]->getNextMenu();
	if (this->current_ == Menus::EXIT)
	{
		this->window_->Close();
		this->current_ = Menus::MAIN;
	}
	this->menus_[this->current_]->update();
}

void	MenuManager::draw()
{
	this->menus_[this->current_]->draw();
}

AEvent	*MenuManager::getEvent()
{
	if (this->event_)
	{
		AEvent* tmp = this->event_;
		this->event_ = 0;
		return tmp;
	}
	return this->menus_[this->current_]->getEvent();
}

void	MenuManager::treatmentEventListRoom(AEvent const* event)
{
	if (this->current_ == Menus::LIST_ROOM)
		dynamic_cast<ListRoomMenu*>(this->menus_[this->current_])->setListRoom(dynamic_cast<EventRoomList const*>(event)->getListRoom());
}

void	MenuManager::treatmentEventNotifyJoin(AEvent const* event)
{
	this->current_ = Menus::ROOM;
	EventGeneric const* tmp = dynamic_cast<EventGeneric const*>(event);
	this->room_.id = tmp->getInt();
	this->room_.portRecv = tmp->getShort();
	this->room_.portSend = tmp->getLong();
	this->room_.config = tmp->getChar();
	dynamic_cast<RoomMenu*>(this->menus_[this->current_])->clearPlayer();
}

void	MenuManager::treatmentEventNotifyPlayer(AEvent const* event)
{
	if (this->current_ == Menus::ROOM)
	{
		EventGeneric const* tmp = dynamic_cast<EventGeneric const*>(event);
		if (!tmp->getChar())
			dynamic_cast<RoomMenu*>(this->menus_[this->current_])->addPlayer(tmp->getString());
		else
			dynamic_cast<RoomMenu*>(this->menus_[this->current_])->deletePlayer(tmp->getString());
	}
}

void	MenuManager::treatmentEventNotifyReady(AEvent const* event)
{
	if (this->current_ == Menus::ROOM)
		this->room_.nbPlayersReady = dynamic_cast<EventGeneric const*>(event)->getInt();
}

void	MenuManager::treatmentEventStartGame(AEvent const* event)
{
	if (this->current_ == Menus::ROOM && !this->event_)
	{
		dynamic_cast<RoomMenu*>(this->menus_[this->current_])->clearPlayer();
		EventGeneric* tmp = new EventGeneric;
		tmp->setType(RTCP::LAUNCH_GAME);
		tmp->setShort(this->room_.portRecv);
		tmp->setLong(this->room_.portSend);
		tmp->setChar(dynamic_cast<EventGeneric const*>(event)->getChar());
		this->event_ = tmp;
		this->current_ = Menus::LOADING;
	}
}

void	MenuManager::treatmentEventNetworkConnected(AEvent const*)
{
	this->current_ = Menus::MAIN;
}

void	MenuManager::treatmentEventNetworkDisconnected(AEvent const*)
{
	this->current_ = Menus::ERROR_NETWORK;
}

void	MenuManager::treatmentEventNotifyGameEnd(AEvent const* event)
{
	this->current_ = Menus::SCORES;
	EventGameEnd const	*tmp = dynamic_cast<EventGameEnd const *>(event);
	dynamic_cast<ScoresMenu *>(this->menus_[this->current_])->setScores(tmp->getScorePlayer(), tmp->getScoreTotal(), tmp->getStatus());
	this->event_ = new AEvent;
	this->event_->setType(RTCP::GAME_NOTIFY_END);
}

void	MenuManager::treatmentEventGamePause(AEvent const*)
{
	this->current_ = Menus::PAUSE;
}

void	MenuManager::setEvent(AEvent const* event)
{
	if (this->ptrF_.find(event->getType()) != this->ptrF_.end())
		(this->*ptrF_[event->getType()])(event);
	delete event;
}
