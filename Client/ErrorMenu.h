
#pragma once

#include "AMenu.h"
#include <SFML/Graphics.hpp>

class ErrorMenu : public AMenu
{
private:
	int current_;
	sf::Image imageCursor_;
	IDrawable* cursor_;
	AEvent* event_;

public:
	ErrorMenu(sf::RenderWindow* win);
	virtual ~ErrorMenu();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual AEvent* getEvent();
	virtual void reset();
};