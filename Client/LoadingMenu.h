
#pragma once

#include "AMenu.h"

class LoadingMenu : public AMenu
{
public:
	LoadingMenu(sf::RenderWindow*);
	virtual ~LoadingMenu();
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual AEvent* getEvent();
	virtual void reset();
};