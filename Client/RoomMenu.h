
#pragma once

#include "AMenu.h"
#include "MenuManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class RoomMenu : public AMenu
{
private:
	int current_;
	sf::Image imageCursor_;
	sf::Image imageReady_;
	sf::Image imageReadyPressed_;
	IDrawable* cursor_;
	IDrawable* buttonReady_;
	IDrawable* buttonReadyPressed_;
	bool buttonReadyFlag_;
	sf::Font font_;
	sf::String text_;
	AEvent* event_;
	MenuManager::Room& room_;
	std::vector<std::string> players_;
	std::string username_;

public:
	RoomMenu(sf::RenderWindow*, MenuManager::Room& room, std::string const& username);
	virtual ~RoomMenu();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual AEvent* getEvent();
	virtual void reset();
	void addPlayer(std::string const& username);
	void deletePlayer(std::string const& username);
	void clearPlayer();
};