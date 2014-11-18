#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

class IDrawable
{
public:
	virtual ~IDrawable(){}
	virtual void animate(float angle) = 0;
	virtual void draw() = 0;
	virtual float getTimeInMs() = 0;
	virtual void setPosX(int) = 0;
	virtual void setPosY(int) = 0;
	virtual bool EndingAnim() const = 0;
};

#else

class IDrawable;

#endif