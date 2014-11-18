#ifndef __OBJ_H__
#define __OBJ_H__

#include <utility>
#include "IDrawable.h"

class	Obj
{
public:
	enum eState
	{
		PLAYER_ONE_ALIVE,
		PLAYER_ONE_DEAD,
		PLAYER_TWO_ALIVE,
		PLAYER_TWO_DEAD,
		PLAYER_THREE_ALIVE,
		PLAYER_THREE_DEAD,
		PLAYER_FOUR_ALIVE,
		PLAYER_FOUR_DEAD,
		ENEMY_ALIVE_1,
		ENEMY_ALIVE_2,
		ENEMY_ALIVE_3,
		ENEMY_ALIVE_4,
		ENEMY_DEAD,
		BULLET_P1_SPAWN,
		BULLET_P2_SPAWN,
		BULLET_P3_SPAWN,
		BULLET_P4_SPAWN,
		BULLET_MOB_SPAWN,
		BULLET_DESTROY,
		BONUS_SPAWN,
		BONUS_PICKED,
		BACKGROUND,
		BACKGROUND2,
		LAST
	};
	struct Position
	{
		float posX;
		float posY;
		int angle;
		int speed;
	};

private:
	eState state_;
	Position pos_;
	int type_;
	IDrawable* sprite_;
	bool isDead_;

public:
	Obj();
	~Obj();

	void setPos(Position const& pos);
	void setPos(unsigned int posX, unsigned int posY, int angle, int speed);
	void setState(eState state);
	void setType(int type);
	void setSprite(IDrawable *sprite);
	IDrawable* unsetSprite();
	void setDead(bool st);
	static float myRound(float val);
	Position const& getPos() const;
	eState getState() const;
	int getType() const;
	bool isDead() const;
	bool isSetSprite() const;
	void draw();
	void update();

};

#else

class	Obj;

#endif
