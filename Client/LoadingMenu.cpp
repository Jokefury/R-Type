
#include "LoadingMenu.h"
#include "SFMLDrawable.h"

LoadingMenu::LoadingMenu(sf::RenderWindow* win)
	: AMenu(win)
{
	this->reset();
}

LoadingMenu::~LoadingMenu()
{
}

void LoadingMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/loading_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
}

void LoadingMenu::update()
{
	this->getKeyEvent();
}

void LoadingMenu::draw()
{
	this->background_->draw();
}

AEvent* LoadingMenu::getEvent()
{
	return 0;
}

void LoadingMenu::reset()
{
	this->nextMenu_ = Menus::LOADING;
}