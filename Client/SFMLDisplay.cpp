
#include "SFMLDisplay.h"
#include "EventGeneric.h"
#include "SFMLDrawable.h"

SFMLDisplay::SFMLDisplay(std::list<Obj *>& objs, std::string const& username)
:	game_(0),
	menu_(0),
	window_(0),
	objs_(objs),
	username_(username),
	event_(0),
	pause_(false)
{
}


SFMLDisplay::~SFMLDisplay(void)
{
	if (this->window_)
		this->window_->Close();
	if (this->game_)
	  delete this->game_;
	if (this->event_)
	  delete this->event_;
	delete this->window_;
	delete this->menu_;
}

void SFMLDisplay::init()
{
	this->window_ = new sf::RenderWindow();

	this->menu_ = new MenuManager(this->window_, this->username_);

	this->window_->Create(sf::VideoMode(800, 600, 32), "R-Type");	
	this->window_->SetFramerateLimit(60);

	this->menu_->draw();
	this->window_->Display();

	this->menu_->init();
}

void SFMLDisplay::initGame(int idPlayer)
{
	this->game_ = new Game(this->window_, this->objs_, idPlayer);
	this->game_->init();
}

void SFMLDisplay::destroyGame()
{
}

void SFMLDisplay::update()
{
	if (this->game_)
		this->game_->update();
	if (!this->game_ || this->pause_)
		this->menu_->update();
}

void SFMLDisplay::draw()
{
	this->window_->Clear();
	if (this->game_)
		this->game_->draw();
	if (!this->game_ || this->pause_)
		this->menu_->draw();
	this->window_->Display();
}

AEvent	*SFMLDisplay::getEvent()
{
	AEvent	*tmp;
	if (this->game_)
	{
		tmp = this->game_->getEvent();
		if (tmp && tmp->getType() == RTCP::GAME_PAUSE)
		{
			this->pause_ = true;
			this->menu_->setEvent(tmp);
			return 0;
		}
	}
	if (!this->game_ || this->pause_)
	{
		tmp = this->menu_->getEvent();
		if (tmp && tmp->getType() == RTCP::LAUNCH_GAME)
			this->initGame(dynamic_cast<EventGeneric*>(tmp)->getChar());
		else if (tmp && tmp->getType() == RTCP::GAME_RESUME)
		{
			this->pause_ = false;
			this->game_->setPause(false);
			delete tmp;
			return 0;
		}
	}
	return tmp;
}

void	SFMLDisplay::setEvent(AEvent* event)
{
	if ((event->getType() == RTCP::NETWORK_DISCONNECTED ||
		event->getType() == RTCP::GAME_NOTIFY_END) && this->game_)
	{
		delete this->game_;
		this->game_ = 0;
	}
	if (this->game_)
		delete event;
	else
		this->menu_->setEvent(event);
}

bool SFMLDisplay::isOpened() const
{
	return this->window_->IsOpened();
}
