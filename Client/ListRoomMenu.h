
#pragma once

#include "AMenu.h"
#include "MenuManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ListRoomMenu : public AMenu
{
private:
	std::vector<MenuManager::Room> rooms_;
	int current_;
	bool onBack_;
	sf::Image imageCursor_;
	IDrawable* cursor_;
	sf::Font font_;
	sf::String text_;
	AEvent* event_;
	std::string username_;
	sf::Clock clock_;
	bool firstDisplay_;

public:
	ListRoomMenu(sf::RenderWindow*, std::string const& username);
	virtual ~ListRoomMenu();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual AEvent* getEvent();
	virtual void reset();
	void setListRoom(std::vector<MenuManager::Room> const& rooms);
};
