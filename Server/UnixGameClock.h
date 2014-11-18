#pragma once

#include <time.h>
#include <sys/time.h>
#include "IGameClock.h"

class   gameClock : public IGameClock
{
  struct timeval        lastUpdateMark_;
  struct timeval        startMark_;
  unsigned int                elapsedTime;

public:
  gameClock();
  virtual ~gameClock();
  virtual unsigned int       getElapsedTime() const;
  virtual unsigned int        getTotalElapsedTime() const;
  virtual void          update();
};
