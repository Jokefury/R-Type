#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AEvent.h"
#include "Obj.h"
#include "enumClient.h"
#include "SFMLDrawable.h"
#include "BackgroundDrawable.h"
#include "MobBulletDrawable.h"
#include "PauseMenu.h"
#include <queue>

typedef IDrawable *(*Drawable)(sf::Image const&, sf::RenderWindow*, int);

class	Game
{
private:
	typedef AEvent *(Game::*keyPtrf)(eEvents) const;
	typedef std::map<eEvents, keyPtrf>	processKey;
	typedef std::map<eEvents, bool> processDir;
	typedef std::map<Obj::eState, Drawable>	ptrToFactory;
	
	sf::Input const& Input;
	BackgroundDrawable		*background_[4];
	int				playerId_;
	processKey			events_;
	sf::RenderWindow		*window_;
	processDir			keypush_;
	std::map<Obj::eState, sf::Image> images_;
	ptrToFactory			ptrToFactory_;
	std::list<Obj *>&		objs_;
	eEvents				laskey_;
	std::queue<AEvent*>		eventQueue_;
	bool				fire_;
	bool				escapeOn_;
	bool				pause_;

private:
	AEvent	*processMove(eEvents) const;
	AEvent	*processBonus(eEvents) const;
	AEvent	*processFire(eEvents) const;
	AEvent	*processEscape(eEvents) const;
	void	getKeyEvent();

public:
	Game(sf::RenderWindow *, std::list<Obj *>&, int);
	~Game();

	void	init();
	void	draw();
	void	update();
	AEvent	*getEvent();
	void	setPause(bool);
};

#else
class	Game;

#endif
