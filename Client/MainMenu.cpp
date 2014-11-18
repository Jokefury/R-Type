
#include "MainMenu.h"
#include "EventGeneric.h"
#include "SFMLDrawable.h"

MainMenu::MainMenu(sf::RenderWindow* win, std::string const& username)
	: AMenu(win), current_(0), tags_(3), event_(0), username_(username)
{
	this->reset();
}

MainMenu::~MainMenu()
{
}

void MainMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/main_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
	this->imageCursor_.LoadFromFile("../Client/assets/highlight.png");
	this->cursor_ = new SFMLDrawable(this->imageCursor_, this->window_);
	this->tags_[0].nextMenu = Menus::LIST_ROOM;
	this->tags_[0].posX = 220;
	this->tags_[0].posY = 196;
	this->tags_[1].nextMenu = Menus::ROOM;
	this->tags_[1].posX = 220;
	this->tags_[1].posY = 315;
	this->tags_[2].nextMenu = Menus::EXIT;
	this->tags_[2].posX = 220;
	this->tags_[2].posY = 434;
}

void MainMenu::update()
{
	eEvents e = this->getKeyEvent();
	if (e == UP)
	{
		--this->current_;
		if (this->current_ < 0)
			this->current_ = 2;
	}
	else if (e == DOWN)
		this->current_ = (this->current_ + 1) % 3;
	else if (e == ENTER)
	{
		this->nextMenu_ = this->tags_[this->current_].nextMenu;
		if (this->nextMenu_ == Menus::ROOM && !this->event_)
		{
			EventGeneric* tmp = new EventGeneric;
			tmp->setType(RTCP::ROOM_CREATE);
			tmp->setChar(0);
			tmp->setString(this->username_);
			this->event_ = tmp;
		}
	}
	this->cursor_->setPosX(this->tags_[this->current_].posX);
	this->cursor_->setPosY(this->tags_[this->current_].posY);
}

void MainMenu::draw()
{
	this->background_->draw();
	this->cursor_->draw();
}

AEvent* MainMenu::getEvent()
{
	AEvent* tmp = this->event_;
	this->event_ = 0;
	return tmp;
}

void MainMenu::reset()
{
	this->nextMenu_ = Menus::MAIN;
}