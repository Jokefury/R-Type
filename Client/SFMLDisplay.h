
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "IGui.h"
#include "enumClient.h"
#include "Game.h"
#include "MenuManager.h"
#include "AEvent.h"

class SFMLDisplay : public IGui
{
private:
	Game			*game_;
	MenuManager		*menu_;
	sf::RenderWindow	*window_;
	std::list<Obj *>&	objs_;
	std::string		username_;
	AEvent*			event_;
	bool			pause_;

private:
	void initGame(int idPlayer);
	void destroyGame();

public:
	SFMLDisplay(std::list<Obj *>&, std::string const& username);
	virtual ~SFMLDisplay(void);

	virtual void	init();
	virtual void	draw();
	virtual void	update();
	virtual AEvent	*getEvent();
	virtual void	setEvent(AEvent* event);
	virtual bool	isOpened() const;
};
