#include "PauseMenu.h"
#include "SFMLDrawable.h"
#include "EventInput.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow *win) : AMenu(win), cursor_(0), coords_(2), event_(0)
{
}

PauseMenu::~PauseMenu()
{
}

void	PauseMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/pause_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
	this->cursorImg_.LoadFromFile("../Client/assets/highlight.png");
	this->cursor_ = new SFMLDrawable(this->cursorImg_, this->window_);
	this->nextMenu_ = Menus::PAUSE;
	this->coords_[0] = std::make_pair(220, 177);
	this->coords_[1] = std::make_pair(220, 323);
	this->current_ = 0;
	this->processFuncs_[UP] = &PauseMenu::processUp;
	this->processFuncs_[DOWN] = &PauseMenu::processDown;
	this->processFuncs_[ENTER] = &PauseMenu::processEnter;
}

void	PauseMenu::update()
{
	eEvents	e = this->getKeyEvent();
	if ((e == UP) ^ (e == DOWN) ^ (e == ENTER) ^ (e == ESCAPE))
		(this->*processFuncs_.at(e))();
	this->cursor_->setPosX(this->coords_.at(this->current_).first);
	this->cursor_->setPosY(this->coords_.at(this->current_).second);
}

void	PauseMenu::draw()
{
	this->background_->draw();
	this->cursor_->draw();
}

AEvent	*PauseMenu::getEvent()
{
	AEvent* tmp = this->event_;
	this->event_ = 0;
	return tmp;
}

void	PauseMenu::reset()
{
	this->nextMenu_ = Menus::PAUSE;
}

void	PauseMenu::processUp()
{
	if (--this->current_ < 0)
		this->current_ = 1;
}

void	PauseMenu::processDown()
{
	if (++this->current_ > 1)
		this->current_ = 0;
}

void	PauseMenu::processEnter()
{
	if (!this->current_)
	{
		EventInput	* tmp = new EventInput;
		tmp->setType(RTCP::GAME_RESUME);
		this->event_ = tmp;
	}
	else
		this->nextMenu_ = Menus::EXIT;
}