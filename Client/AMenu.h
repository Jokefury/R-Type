#ifndef __AMENU_H__
#define __AMENU_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include "IDrawable.h"
#include "enumClient.h"
#include "AEvent.h"
#include <map>

class	AMenu
{
private:
	std::map<sf::Key::Code, eEvents> keyMapping_;	

protected:
	sf::Clock			cl_;
	sf::RenderWindow	*window_;
	sf::Image			image_;
	IDrawable			*background_;
	Menus::eMenus		nextMenu_;

protected:
	virtual eEvents getKeyEvent();

public:
	AMenu(sf::RenderWindow *);
	virtual ~AMenu();

	virtual void	init() = 0;
	virtual void	update() = 0;
	virtual void	draw() = 0;
	virtual AEvent* getEvent() = 0;
	virtual void reset() = 0;
	virtual Menus::eMenus getNextMenu();
};

#else

class	AMenu;

#endif