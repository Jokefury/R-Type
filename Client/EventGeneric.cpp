
#include "EventGeneric.h"

EventGeneric::EventGeneric()
{
}

EventGeneric::~EventGeneric()
{
}

void EventGeneric::setChar(char c)
{
	this->c_ = c;
}

void EventGeneric::setString(std::string const& str)
{
	this->str_ = str;
}

void EventGeneric::setInt(unsigned int nb)
{
	this->nb_ = nb;
}

void EventGeneric::setShort(short s)
{
	this->short_ = s;
}

void EventGeneric::setLong(long nb)
{
	this->nb2_ = nb;
}

char EventGeneric::getChar() const
{
	return this->c_;
}

std::string const& EventGeneric::getString() const
{
	return this->str_;
}

unsigned int EventGeneric::getInt() const
{
	return this->nb_;
}

short EventGeneric::getShort() const
{
	return this->short_;
}

long EventGeneric::getLong() const
{
	return this->nb2_;
}