
#pragma once

#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include "enumClient.h"
#include "AEvent.h"
#include "AMenu.h"

class	MenuManager
{
private:
	typedef void (MenuManager::*eventFunc)(AEvent const* event);

public:
	struct Room
	{
		int id;
		short nbPlayers;
		int nbPlayersReady;
		int portRecv;
		int portSend;
		char config;
		char launched;
	};

private:
	sf::RenderWindow			*window_;
	Menus::eMenus				current_;
	std::map<Menus::eMenus, AMenu *>	menus_;
	std::map<RTCP::eRequest, eventFunc>	ptrF_;
	Room					room_;
	std::string				username_;
	AEvent					*event_;
	bool					pause_;

private:
	void treatmentEventListRoom(AEvent const* event);
	void treatmentEventNotifyJoin(AEvent const* event);
	void treatmentEventNotifyPlayer(AEvent const* event);
	void treatmentEventNotifyReady(AEvent const* event);
	void treatmentEventStartGame(AEvent const* event);
	void treatmentEventNetworkConnected(AEvent const* event);
	void treatmentEventNetworkDisconnected(AEvent const* event);
	void treatmentEventNotifyGameEnd(AEvent const* event);
	void treatmentEventGamePause(AEvent const* event);

public:
	MenuManager(sf::RenderWindow *, std::string const& username);
	~MenuManager();

	void	init();
	void	update();
	void	draw();
	AEvent	*getEvent();
	void	setEvent(AEvent const* event);
};
