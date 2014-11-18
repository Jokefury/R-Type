
#include "ErrorMenu.h"
#include "SFMLDrawable.h"

static const unsigned int gWinPos[2][2] = {
	{166, 417},
	{443, 417}
};

ErrorMenu::ErrorMenu(sf::RenderWindow* win)
	: AMenu(win), current_(0), event_(0)
{
	this->reset();
}

ErrorMenu::~ErrorMenu()
{
}

void ErrorMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/error_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
	this->imageCursor_.LoadFromFile("../Client/assets/highlight_small.png");
	this->cursor_ = new SFMLDrawable(this->imageCursor_, this->window_);
}

void ErrorMenu::update()
{
	eEvents e = this->getKeyEvent();
	if (e == LEFT || e == RIGHT)
		(this->current_) ? (this->current_ = 0) : (this->current_ = 1);
	else if (e == ENTER)
	{
		if (!this->current_ && !this->event_)
		{
			this->event_ = new AEvent;
		}
		else
		{
			this->nextMenu_ = Menus::EXIT;
		}
	}
	this->cursor_->setPosX(gWinPos[this->current_][0]);
	this->cursor_->setPosY(gWinPos[this->current_][1]);
}

void ErrorMenu::draw()
{
	this->background_->draw();
	this->cursor_->draw();
}

AEvent* ErrorMenu::getEvent()
{
	AEvent* tmp = this->event_;
	this->event_ = 0;
	return tmp;
}

void ErrorMenu::reset()
{
	this->nextMenu_ = Menus::ERROR_NETWORK;
}