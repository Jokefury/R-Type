
#pragma once

#include "AEvent.h"
#include <string>

class EventGeneric : public AEvent
{
private:
	char c_;
	std::string str_;
	unsigned int nb_;
	long nb2_;
	short short_;

public:
	EventGeneric();
	virtual ~EventGeneric();
	void setChar(char c);
	void setString(std::string const& str);
	void setInt(unsigned int);
	void setShort(short);
	void setLong(long);
	char getChar() const;
	std::string const& getString() const;
	unsigned int getInt() const;
	short getShort() const;
	long getLong() const;
};