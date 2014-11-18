
#include "ListRoomMenu.h"
#include "SFMLDrawable.h"
#include "EventGeneric.h"
#include <sstream>

static const unsigned int gWinPos[8][2] = {
	{300, 165},
	{300, 215},
	{300, 265},
	{300, 315},
	{300, 365},
	{300, 415},
	{300, 465},
	{300, 515},
};

ListRoomMenu::ListRoomMenu(sf::RenderWindow* win, std::string const& username)
	: AMenu(win), current_(0), onBack_(true), event_(0), username_(username), firstDisplay_(true)
{
	this->clock_.Reset();
	this->reset();
}

ListRoomMenu::~ListRoomMenu()
{
}

void ListRoomMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/list_room_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
	this->imageCursor_.LoadFromFile("../Client/assets/cursor_menu.png");
	this->cursor_ = new SFMLDrawable(this->imageCursor_, this->window_);
	this->font_.LoadFromFile("../Client/assets/space.ttf");
	this->text_.SetFont(this->font_);
	this->text_.SetSize(40);
	this->onBack_ = true;
	this->cursor_->setPosX(595);
	this->cursor_->setPosY(535);
}

void ListRoomMenu::update()
{
	if ((this->firstDisplay_ || this->clock_.GetElapsedTime() > 4.0f) && !this->event_)
	{
		this->event_ = new AEvent;
		this->event_->setType(RTCP::ROOM_GET_LIST);
		this->clock_.Reset();
		this->firstDisplay_ = false;
	}
	eEvents e = this->getKeyEvent();
	if (e == ENTER)
	{
		if (this->onBack_)
			this->nextMenu_ = Menus::MAIN;
		else if (!this->rooms_[this->current_].launched)
		{
			if (!this->event_)
			{
				this->event_ = new EventGeneric;
				this->event_->setType(RTCP::ROOM_JOIN);
				dynamic_cast<EventGeneric*>(this->event_)->setInt(this->rooms_[this->current_].id);
				dynamic_cast<EventGeneric*>(this->event_)->setString(this->username_);
				this->firstDisplay_ = true;
			}
		}
	}
	if (!this->rooms_.size())
		return ;
	if (e == LEFT || e == RIGHT)
		(this->onBack_) ? (this->onBack_ = false) : (this->onBack_ = true);
	else if (!this->onBack_ && e == UP)
	{
		--this->current_;
		if (this->current_ < 0)
			this->current_ = this->rooms_.size() - 1;
	}
	else if (!this->onBack_ && e == DOWN)
		this->current_ = (this->current_ + 1) % this->rooms_.size();
	if (this->onBack_)
	{
		this->cursor_->setPosX(595);
		this->cursor_->setPosY(535);
	}
	else
	{
		unsigned int i = this->current_ % 8;
		this->cursor_->setPosX(gWinPos[i][0] - 65);
		this->cursor_->setPosY(gWinPos[i][1] + 5);
	}
}

void ListRoomMenu::draw()
{
	this->background_->draw();
	this->cursor_->draw();
	int tmp = this->current_ - this->current_ % 8;
	if (tmp < 0)
		tmp = 0;
	for (unsigned int i = 0; i < 8 && static_cast<unsigned int>(tmp) < this->rooms_.size(); ++i, ++tmp)
	{
		std::stringstream ss;
		ss << "Room " << this->rooms_[tmp].id << '(' << this->rooms_[tmp].nbPlayers << ')';
		this->text_.SetText(ss.str());
		if (this->rooms_[i].launched)
			this->text_.SetColor(sf::Color(255, 0, 0));
		else
		  this->text_.SetColor(sf::Color(255, 255, 255));
		this->text_.SetPosition(static_cast<float>(gWinPos[i][0]), static_cast<float>(gWinPos[i][1]));
		this->window_->Draw(this->text_);
	}
}

AEvent* ListRoomMenu::getEvent()
{
	AEvent* tmp = this->event_;
	this->event_ = 0;
	return tmp;
}

void ListRoomMenu::reset()
{
	this->nextMenu_ = Menus::LIST_ROOM;
}

void ListRoomMenu::setListRoom(std::vector<MenuManager::Room> const& rooms)
{
	this->rooms_ = rooms;
	this->current_ = this->rooms_.size() - 1;
	if (!this->rooms_.size())
	  {
	    this->onBack_ = true;
	    this->current_ = 0;
	  }
}
