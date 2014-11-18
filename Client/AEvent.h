#ifndef __AEVENT_H__
#define __AEVENT_H__

#include "RTCP.h"

class	AEvent
{
private:
	RTCP::eRequest	_type;

public:
	AEvent();
	virtual ~AEvent();

	virtual	RTCP::eRequest	getType() const;
	virtual void	setType(RTCP::eRequest);
};

#else

class	AEvent;

#endif