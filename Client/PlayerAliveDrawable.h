#pragma once

#include "IDrawable.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Obj.h"

class PlayerAliveDrawable : public IDrawable
{
private:
	sf::Clock cl_;
	sf::RenderWindow* win_;
	sf::Sprite sprite_;
	float width_;
	float height_;
	int posX_;
	int posY_;
	float elapsedTime_;
	bool alternateMove_;
	
public:
	PlayerAliveDrawable(sf::Image const& img, sf::RenderWindow* ptr, int type);
	virtual bool EndingAnim() const;
	virtual ~PlayerAliveDrawable(void);
	virtual	void animate(float angle);
	virtual	void draw();
	virtual float getTimeInMs();
	virtual void setPosX(int x);
	virtual void setPosY(int y);
	int state_;

public:
	static IDrawable *factory(sf::Image const& img, sf::RenderWindow* ptr, int type) { return new PlayerAliveDrawable(img, ptr, type); } 
};

