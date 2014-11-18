#include "AMenu.h"
#include "SFMLDrawable.h"
#include <map>
#include <iostream>

AMenu::AMenu(sf::RenderWindow *win)
	: window_(win), background_(0)
{
	this->keyMapping_[sf::Key::Up] = UP;
	this->keyMapping_[sf::Key::Down] = DOWN;	
	this->keyMapping_[sf::Key::Left] = LEFT;
	this->keyMapping_[sf::Key::Right] = RIGHT;
	this->cl_.Reset();
}

AMenu::~AMenu()
{
	delete this->background_;
}

eEvents AMenu::getKeyEvent()
{
	sf::Event e;
	eEvents ret = NOTHING;

	while (this->window_->GetEvent(e))
	{
		if (e.Type == sf::Event::Closed)
			this->window_->Close();
		if (e.Type == sf::Event::KeyReleased && e.Key.Code == sf::Key::Return)
			ret = ENTER;
		else if (this->cl_.GetElapsedTime() > 0.20f && e.Type == sf::Event::KeyPressed)
		{
			if (this->keyMapping_.find(e.Key.Code) != this->keyMapping_.end())
				ret = this->keyMapping_[e.Key.Code];
			this->cl_.Reset();
		}
	}
	return ret;
}

Menus::eMenus AMenu::getNextMenu()
{
	Menus::eMenus tmp = this->nextMenu_;
	this->reset();
	return tmp;
}
