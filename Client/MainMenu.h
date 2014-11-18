
#pragma once

#include "AMenu.h"
#include <vector>

class MainMenu : public AMenu
{
private:
	struct Tag
	{
		unsigned int posX;
		unsigned int posY;
		Menus::eMenus nextMenu;
	};

private:
	int current_;
	sf::Image imageCursor_;
	IDrawable* cursor_;
	std::vector<Tag> tags_;
	AEvent* event_;
	std::string username_;

public:
	MainMenu(sf::RenderWindow*, std::string const& username);
	virtual ~MainMenu();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual AEvent* getEvent();
	virtual void reset();
};