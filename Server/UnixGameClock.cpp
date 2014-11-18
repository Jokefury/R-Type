#include        "UnixGameClock.h"

gameClock::gameClock() :
  elapsedTime (0.0)
{
  gettimeofday(&startMark_, NULL);
  gettimeofday(&lastUpdateMark_, NULL);
}

gameClock::~gameClock()
{

}

unsigned int  gameClock::getTotalElapsedTime() const
{
  unsigned int        totalElapsedTime;

  totalElapsedTime = (lastUpdateMark_.tv_sec - startMark_.tv_sec) * 1000;
  totalElapsedTime += (lastUpdateMark_.tv_usec - startMark_.tv_usec) / 1000;
  return totalElapsedTime;
}

unsigned int  gameClock::getElapsedTime() const
{
  return elapsedTime;
}

void    gameClock::update()
{
  struct timeval        t;

  gettimeofday (&t, NULL);
  elapsedTime = (t.tv_sec - lastUpdateMark_.tv_sec) * 1000;
  elapsedTime += (t.tv_usec - lastUpdateMark_.tv_usec) / 1000;
  lastUpdateMark_ = t;
}
