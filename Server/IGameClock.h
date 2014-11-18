#pragma once

class   IGameClock
{
public:
	virtual	~IGameClock(){}
  virtual unsigned int       getElapsedTime() const = 0;
  virtual unsigned int       getTotalElapsedTime() const = 0;
  virtual void          update() = 0;
};
