#include "Game.h"
#include "EventInput.h"
#include "SFMLDrawable.h"
#include <algorithm>
#include "EnemyDrawable.h"
#include "BulletDrawable.h"
#include "PlayerAliveDrawable.h"
#include "ExplosionDrawable.h"
#include <iostream>

Game::Game(sf::RenderWindow *win, std::list<Obj *>& objs, int playerId)
  :  Input(win->GetInput()),
     playerId_(playerId),
     objs_(objs)
{
	this->window_ = win;
}

Game::~Game()
{
	delete this->background_[0];
	delete this->background_[1];
	this->objs_.erase(this->objs_.begin(), this->objs_.end());
	while (!this->eventQueue_.empty())
	{
		delete this->eventQueue_.front();
		this->eventQueue_.pop();
	}
}

void	Game::init()
{
	this->ptrToFactory_[Obj::PLAYER_ONE_ALIVE] = &PlayerAliveDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_TWO_ALIVE] = &PlayerAliveDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_THREE_ALIVE] = &PlayerAliveDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_FOUR_ALIVE] = &PlayerAliveDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_P1_SPAWN] = &BulletDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_P2_SPAWN] = &BulletDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_P3_SPAWN] = &BulletDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_P4_SPAWN] = &BulletDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_MOB_SPAWN] = &MobBulletDrawable::factory;
	this->ptrToFactory_[Obj::BULLET_DESTROY] = &BulletDrawable::factory;
	this->ptrToFactory_[Obj::ENEMY_ALIVE_1] = &EnemyDrawable::factory;
	this->ptrToFactory_[Obj::ENEMY_ALIVE_2] = &EnemyDrawable::factory;
	this->ptrToFactory_[Obj::ENEMY_ALIVE_3] = &EnemyDrawable::factory;
	this->ptrToFactory_[Obj::ENEMY_ALIVE_4] = &EnemyDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_ONE_DEAD] = &ExplosionDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_TWO_DEAD] = &ExplosionDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_THREE_DEAD] = &ExplosionDrawable::factory;
	this->ptrToFactory_[Obj::PLAYER_FOUR_DEAD] = &ExplosionDrawable::factory;
	this->ptrToFactory_[Obj::ENEMY_DEAD] = &ExplosionDrawable::factory;
	fire_ = false;
	this->events_[NOTHING] =  &Game::processMove;
	this->events_[UP] = &Game::processMove;
	this->events_[DOWN] = &Game::processMove;
	this->events_[LEFT] = &Game::processMove;
	this->events_[RIGHT] = &Game::processMove;
	this->events_[UPLEFT] = &Game::processMove;
	this->events_[UPRIGHT] = &Game::processMove;
	this->events_[DOWNLEFT] = &Game::processMove;
	this->events_[DOWNRIGHT] = &Game::processMove;
	this->events_[FIRE] = &Game::processFire;
	this->events_[ESCAPE] = &Game::processEscape;
	this->images_[Obj::PLAYER_ONE_ALIVE].LoadFromFile("../Client/assets/player_one_alive.png");
	this->images_[Obj::PLAYER_TWO_ALIVE].LoadFromFile("../Client/assets/player_one_alive.png");
	this->images_[Obj::PLAYER_THREE_ALIVE].LoadFromFile("../Client/assets/player_one_alive.png");
	this->images_[Obj::PLAYER_FOUR_ALIVE].LoadFromFile("../Client/assets/player_one_alive.png");
	this->images_[Obj::ENEMY_ALIVE_1].LoadFromFile("../Client/assets/enemy_alive.png");
	this->images_[Obj::ENEMY_ALIVE_2].LoadFromFile("../Client/assets/enemy_alive3.png");
	this->images_[Obj::ENEMY_ALIVE_3].LoadFromFile("../Client/assets/enemy_alive4.png");
	this->images_[Obj::ENEMY_ALIVE_4].LoadFromFile("../Client/assets/enemy_alive2.png");
	this->images_[Obj::BULLET_P1_SPAWN].LoadFromFile("../Client/assets/bullet_spawn.png");
	this->images_[Obj::BULLET_P2_SPAWN].LoadFromFile("../Client/assets/bullet_spawnp2.png");
	this->images_[Obj::BULLET_P3_SPAWN].LoadFromFile("../Client/assets/bullet_spawnp3.png");
	this->images_[Obj::BULLET_P4_SPAWN].LoadFromFile("../Client/assets/bullet_spawnp4.png");
	this->images_[Obj::BULLET_MOB_SPAWN].LoadFromFile("../Client/assets/bullet_spawn.png");
	this->images_[Obj::BACKGROUND].LoadFromFile("../Client/assets/background.png");
	this->images_[Obj::BACKGROUND2].LoadFromFile("../Client/assets/middleground.png");
	this->images_[Obj::PLAYER_ONE_DEAD].LoadFromFile("../Client/assets/explosprite.png");
	this->images_[Obj::PLAYER_TWO_DEAD].LoadFromFile("../Client/assets/explosprite.png");
	this->images_[Obj::PLAYER_THREE_DEAD].LoadFromFile("../Client/assets/explosprite.png");
	this->images_[Obj::PLAYER_FOUR_DEAD].LoadFromFile("../Client/assets/explosprite.png");
	this->images_[Obj::ENEMY_DEAD].LoadFromFile("../Client/assets/explosprite.png");
	this->background_[0] = new BackgroundDrawable(this->images_[Obj::BACKGROUND], this->window_, 1);
	this->background_[1] = new BackgroundDrawable(this->images_[Obj::BACKGROUND], this->window_, 1);
	this->background_[2] = new BackgroundDrawable(this->images_[Obj::BACKGROUND2], this->window_, 2);
	this->background_[3] = new BackgroundDrawable(this->images_[Obj::BACKGROUND2], this->window_, 2);
	this->background_[0]->setPosX(0);
	this->background_[0]->setPosY(0);
	this->background_[1]->setPosX(800);
	this->background_[1]->setPosY(0);
	this->background_[2]->setPosX(0);
	this->background_[2]->setPosY(0);
	this->background_[3]->setPosX(800);
	this->background_[3]->setPosY(0);
	this->keypush_[NOTHING] = false;
	this->keypush_[UP] =false;
	this->keypush_[DOWN] =false;
	this->keypush_[LEFT] =false;
	this->keypush_[RIGHT] =false;
	this->keypush_[UPLEFT] =false;
	this->keypush_[UPRIGHT] =false;
	this->keypush_[DOWNLEFT] =false;
	this->keypush_[DOWNRIGHT] =false;
	this->pause_ = false;
	this->escapeOn_ = false;
}

void	Game::update()
{	
  if (!this->pause_)
    this->getKeyEvent();
  this->background_[0]->animate(0);
  this->background_[1]->animate(0);
  this->background_[2]->animate(0);
  this->background_[3]->animate(0);
  
  for (std::list<Obj *>::iterator it = this->objs_.begin(); it != this->objs_.end(); ++it)
    {
      if ((*it)->isDead() == true)
	if ((it = this->objs_.erase(it)) == this->objs_.end())
	  break ;	  
      if (!(*it)->isSetSprite())
	(*it)->setSprite(this->ptrToFactory_[(*it)->getState()](this->images_[(*it)->getState()],
								this->window_, (*it)->getType()));
      (*it)->update();
    }
}

void	Game::draw()
{
	this->background_[0]->draw();
	this->background_[1]->draw();
	this->background_[2]->draw();
	this->background_[3]->draw();
	for (std::list<Obj *>::iterator it = this->objs_.begin(); it != this->objs_.end(); ++it)
		(*it)->draw();
}

static bool pred(std::pair<eEvents, bool>  a)
{
	return a.second;
}

void	Game::getKeyEvent()
{
	AEvent	*tmp;
	processDir::iterator it;
	sf::Event Event;
	
	while (this->window_->GetEvent(Event))
	{
		if (Event.Type == sf::Event::Closed)
			this->window_->Close();
	}
	this->keypush_[LEFT] = Input.IsKeyDown(sf::Key::A) && !Input.IsKeyDown(sf::Key::W) && !Input.IsKeyDown(sf::Key::S) ;
	this->keypush_[RIGHT] = Input.IsKeyDown(sf::Key::D) && !Input.IsKeyDown(sf::Key::W) && !Input.IsKeyDown(sf::Key::S);
	this->keypush_[UP] = Input.IsKeyDown(sf::Key::W) && !Input.IsKeyDown(sf::Key::A) && !Input.IsKeyDown(sf::Key::D);
	this->keypush_[DOWN] = Input.IsKeyDown(sf::Key::S) && !Input.IsKeyDown(sf::Key::A) && !Input.IsKeyDown(sf::Key::D);
	this->keypush_[DOWNLEFT] = Input.IsKeyDown(sf::Key::S) && Input.IsKeyDown(sf::Key::A);
	this->keypush_[UPLEFT] = Input.IsKeyDown(sf::Key::W) && Input.IsKeyDown(sf::Key::A);
	this->keypush_[UPRIGHT] = Input.IsKeyDown(sf::Key::W) && Input.IsKeyDown(sf::Key::D);
	this->keypush_[DOWNRIGHT] = Input.IsKeyDown(sf::Key::S) && Input.IsKeyDown(sf::Key::D);

	it = find_if (this->keypush_.begin(), this->keypush_.end(), pred);
	if (it == this->keypush_.end() && this->laskey_ != NOTHING)
	{
		tmp = (this->*events_.at(NOTHING))(NOTHING);
		this->laskey_ = NOTHING;
		this->eventQueue_.push(tmp);
	}
	else if (it != this->keypush_.end() && this->laskey_ != (*it).first)
	{
		tmp = (this->*events_.at((*it).first))((*it).first);
		this->eventQueue_.push(tmp);
		this->laskey_ = (*it).first;
	}
	if (Input.IsKeyDown(sf::Key::Space))
		this->fire_ = true;
	if (!Input.IsKeyDown(sf::Key::Space) && this->fire_ == true)
	{
		this->fire_ = false;
		tmp = (this->*events_.at(FIRE))(FIRE);
		this->eventQueue_.push(tmp);
	}
	if (Input.IsKeyDown(sf::Key::Escape))
		this->escapeOn_ = true;
	else if (this->escapeOn_)
	{
		this->escapeOn_ = false;
		this->pause_ = true;
		tmp = (this->*events_.at(ESCAPE))(ESCAPE);
		this->eventQueue_.push(tmp);
	}
}

AEvent	*Game::getEvent()
{
	if (!this->eventQueue_.empty())
	{
		AEvent *tmp = this->eventQueue_.front();
		this->eventQueue_.pop();
		return tmp;
	}
	return 0;
}

AEvent	*Game::processMove(eEvents e) const
{ 
	EventInput	*ret = new EventInput;
	ret->setType(RTCP::GAME_MOVE);
	ret->setId(this->playerId_);
	ret->setAngle(e);
	return ret;
}

AEvent	*Game::processBonus(eEvents) const
{
	return 0;
}

AEvent	*Game::processFire(eEvents)  const
{
	EventInput	*ret = new EventInput;
	ret->setType(RTCP::GAME_LAUNCH_SHOT);
	ret->setId(this->playerId_);
	return ret;
}

AEvent	*Game::processEscape(eEvents) const
{
	EventInput	*ret = new EventInput;
	ret->setType(RTCP::GAME_PAUSE);
	return ret;
}

void	Game::setPause(bool state)
{
	this->pause_ = state;
}

