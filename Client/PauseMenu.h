
#pragma once

#include <vector>
#include <utility>
#include <map>
#include "AMenu.h"

class	PauseMenu : public AMenu
{
private:
	typedef void	(PauseMenu::*ptrf)();

	sf::Image		cursorImg_;
	IDrawable		*cursor_;
	int				current_;
	std::map<eEvents, ptrf>	processFuncs_;
	std::vector<std::pair<unsigned int, unsigned int> >	coords_;
	AEvent			*event_;

private:
	void	processUp();
	void	processDown();
	void	processEnter();

public:
	PauseMenu(sf::RenderWindow *);
	virtual ~PauseMenu();

	virtual void	draw();
	virtual void	init();
	virtual void	update();
	virtual AEvent	*getEvent();
	virtual void	reset();
};
