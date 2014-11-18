#include "AEvent.h"

AEvent::AEvent() : _type(RTCP::LAST)
{
}

AEvent::~AEvent()
{
}

RTCP::eRequest	AEvent::getType() const
{
	return this->_type;
}

void	AEvent::setType(RTCP::eRequest type)
{
	this->_type = type;
}