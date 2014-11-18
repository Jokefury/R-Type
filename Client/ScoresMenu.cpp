#include <sstream>
#include "ScoresMenu.h"
#include "SFMLDrawable.h"

static const unsigned int gScoresPos[2][2] = {
	{150, 300},
	{150, 425}
};

ScoresMenu::ScoresMenu(sf::RenderWindow *win) : AMenu(win)
{
	this->reset();
}

ScoresMenu::~ScoresMenu()
{
}

void	ScoresMenu::init()
{
	this->image_.LoadFromFile("../Client/assets/scores_menu.png");
	this->background_ = new SFMLDrawable(this->image_, this->window_);
	this->background_->setPosX(0);
	this->background_->setPosY(0);
	this->medalImg_.LoadFromFile("../Client/assets/medal.png");
	this->medal_ = new SFMLDrawable(this->medalImg_, this->window_);
	this->medal_->setPosX(gScoresPos[0][0] - 75);
	this->medal_->setPosY(gScoresPos[0][1]);
	this->font_.LoadFromFile("../Client/assets/space.ttf");
	this->text_.SetFont(this->font_);
	this->text_.SetSize(40);
}

void	ScoresMenu::update()
{
	eEvents	e = this->getKeyEvent();
	if (e == ENTER)
		this->nextMenu_ = Menus::MAIN;
}

void	ScoresMenu::draw()
{
	this->background_->draw();

	std::stringstream	ss;
	std::string			tmp;

	ss << this->score_;
	tmp = ss.str();
	this->text_.SetText("Your score:\n" + tmp);
	this->text_.SetPosition(static_cast<float>(gScoresPos[0][0]), static_cast<float>(gScoresPos[0][1]));
	this->window_->Draw(this->text_);

	if (this->higher_)
		this->medal_->draw();

	std::stringstream	ss2;
	ss2 << this->total_;
	tmp = ss2.str();
	this->text_.SetText("Total team score:\n" + tmp);
	this->text_.SetPosition(static_cast<float>(gScoresPos[1][0]), static_cast<float>(gScoresPos[1][1]));
	this->window_->Draw(this->text_);
}

AEvent	*ScoresMenu::getEvent()
{
	return 0;
}

void	ScoresMenu::reset()
{
	this->nextMenu_ = Menus::SCORES;
}

void	ScoresMenu::setScores(int player, int total, char st)
{
	this->score_ = player;
	if (st)
		this->higher_ = true;
	else
		this->higher_ = false;
	this->total_ = total;
	this->status_ = st;
}
