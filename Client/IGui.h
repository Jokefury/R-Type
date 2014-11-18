#ifndef __IGUI_H__
#define __IGUI_H__

#include "AEvent.h"

class	IGui
{
public:
	virtual ~IGui() {}

	virtual void	init() = 0;
	virtual void	draw() = 0;
	virtual void	update() = 0;
	virtual AEvent	*getEvent() = 0;
	virtual void	setEvent(AEvent* event) = 0;
	virtual bool	isOpened() const = 0;
};

#else
class	IGui;

#endif