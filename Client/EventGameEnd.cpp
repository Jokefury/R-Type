
#include "EventGameEnd.h"

EventGameEnd::EventGameEnd()
{
}

EventGameEnd::~EventGameEnd()
{
}

void EventGameEnd::setStatus(char status)
{
  this->status_ = status;
}

void EventGameEnd::setScorePlayer(int j)
{
  this->player_ = j;
}

void EventGameEnd::setScoreTotal(int total)
{
  this->total_ = total;
}

char EventGameEnd::getStatus() const
{
  return this->status_;
}

int EventGameEnd::getScorePlayer() const
{
  return this->player_;
}

int EventGameEnd::getScoreTotal() const
{
  return this->total_;
}
