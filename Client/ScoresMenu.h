#pragma once

#include <vector>
#include "AMenu.h"
#include "AEvent.h"
#include <SFML/Graphics.hpp>

class	ScoresMenu : public AMenu
{
private:
	sf::Image	medalImg_;
	IDrawable	*medal_;
	sf::Font	font_;
	sf::String	text_;
	AEvent		*event_;
	bool		higher_;
	int		score_;
	int		total_;
	char		status_;

public:
	ScoresMenu(sf::RenderWindow *);
	~ScoresMenu();

	void	init();
	void	update();
	void	draw();
	AEvent	*getEvent();
	void	reset();
	void	setScores(int, int, char);
};
