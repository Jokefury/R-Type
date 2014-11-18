
#include "RoomMenu.h"
#include "EventGeneric.h"
#include "SFMLDrawable.h"
#include <algorithm>
#include <sstream>

static const unsigned int gWinPosButton[2][2] = {
  {604, 241},
  {604, 428},
};

static const unsigned int gWinPosPlayer[4][2] = {
  {200, 200},
  {200, 300},
  {200, 400},
  {200, 500},
};

RoomMenu::RoomMenu(sf::RenderWindow* win, MenuManager::Room& room, std::string const& username)
  : AMenu(win), current_(1), event_(0), room_(room), username_(username)
{
  this->reset();
}

RoomMenu::~RoomMenu()
{
}

void RoomMenu::init()
{
  this->image_.LoadFromFile("../Client/assets/room_menu.png");
  this->background_ = new SFMLDrawable(this->image_, this->window_);
  this->background_->setPosX(0);
  this->background_->setPosY(0);
  this->imageCursor_.LoadFromFile("../Client/assets/highlight_small.png");
  this->cursor_ = new SFMLDrawable(this->imageCursor_, this->window_);
  this->imageReady_.LoadFromFile("../Client/assets/ready_button.png");
  this->imageReadyPressed_.LoadFromFile("../Client/assets/ready_pressed_button.png");
  this->buttonReady_ = new SFMLDrawable(this->imageReady_, this->window_);
  this->buttonReady_->setPosX(gWinPosButton[1][0]);
  this->buttonReady_->setPosY(gWinPosButton[1][1]);
  this->buttonReadyPressed_ = new SFMLDrawable(this->imageReadyPressed_, this->window_);
  this->buttonReadyPressed_->setPosX(gWinPosButton[1][0]);
  this->buttonReadyPressed_->setPosY(gWinPosButton[1][1]);
  this->buttonReadyFlag_ = false;
  this->font_.LoadFromFile("../Client/assets/space.ttf");
  this->text_.SetFont(this->font_);
  this->text_.SetSize(50);
  this->cursor_->setPosX(gWinPosButton[this->current_][0]);
  this->cursor_->setPosY(gWinPosButton[this->current_][1]);
}

void RoomMenu::update()
{
  eEvents e = this->getKeyEvent();
  if (e == UP)
    {
      --this->current_;
      if (this->current_ < 0)
        this->current_ = 1;
    }
  else if (e == DOWN)
    this->current_ = (this->current_ + 1) % 2;
  else if (e == ENTER)
    {
      if (this->current_ == 0)
        {
          this->nextMenu_ = Menus::LIST_ROOM;
          if (!this->event_)
            {
              EventGeneric* tmp = new EventGeneric;
              tmp->setType(RTCP::ROOM_LEAVE);
	              tmp->setInt(this->room_.id);
              tmp->setString(this->username_);
              this->event_ = tmp;
            }
        }
      else if (this->current_ == 1 && !this->event_)
        {
          this->buttonReadyFlag_ = true;
          this->event_ = new EventGeneric;
          this->event_->setType(RTCP::ROOM_READY);
          dynamic_cast<EventGeneric*>(this->event_)->setInt(this->room_.id);
        }
    }
  this->cursor_->setPosX(gWinPosButton[this->current_][0]);
  this->cursor_->setPosY(gWinPosButton[this->current_][1]);
}

void RoomMenu::draw()
{
  this->background_->draw();
  (this->buttonReadyFlag_) ? this->buttonReadyPressed_->draw() : this->buttonReady_->draw();
  this->cursor_->draw();
  for (unsigned int i = 0; i < this->players_.size(); ++i)
    {
      this->text_.SetText(this->players_[i]);
      this->text_.SetPosition(static_cast<float>(gWinPosPlayer[i][0]), static_cast<float>(gWinPosPlayer[i][1]));
      this->window_->Draw(this->text_);
    }
  std::stringstream ss;
  ss << this->room_.nbPlayersReady << " / " << this->room_.nbPlayers;
  this->text_.SetText(ss.str());
  this->text_.SetPosition(static_cast<float>(gWinPosButton[1][0] + 30.0f), static_cast<float>(gWinPosButton[1][1] - 50.0f));
  this->window_->Draw(this->text_);
}

AEvent* RoomMenu::getEvent()
{
  AEvent* tmp = this->event_;
  this->event_ = 0;
  return tmp;
}

void RoomMenu::reset()
{
  this->nextMenu_ = Menus::ROOM;
}

void RoomMenu::addPlayer(std::string const& username)
{
  this->players_.push_back(username);
  this->room_.nbPlayers = this->players_.size();
}

void RoomMenu::deletePlayer(std::string const& username)
{
  std::vector<std::string>::iterator it = std::find(this->players_.begin(), this->players_.end(), username);
  if (it != this->players_.end())
    {
      this->players_.erase(it);
      this->room_.nbPlayers = this->players_.size();
    }
}

void RoomMenu::clearPlayer()
{
  this->players_.clear();
  this->buttonReadyFlag_ = false;
}
