#ifndef __EVENTINPUT_H__
#define __EVENTINPUT_H__

#include "AEvent.h"

class	EventInput : public AEvent
{
private:
	int	id_;
	int	angle_;

public:
	EventInput();
	virtual ~EventInput();

	int		getId() const;
	int		getAngle() const;

	void	setId(int);
	void	setAngle(int);
};

#endif