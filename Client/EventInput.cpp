#include "EventInput.h"

EventInput::EventInput() : AEvent()
{
}

EventInput::~EventInput()
{
}

int	EventInput::getId() const
{
	return this->id_;
}

int	EventInput::getAngle() const
{
	return this->angle_;
}

void	EventInput::setId(int id)
{
	this->id_ = id;
}

void	EventInput::setAngle(int angle)
{
	this->angle_ = angle;
}