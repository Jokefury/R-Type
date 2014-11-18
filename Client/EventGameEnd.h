
#pragma once

#include "AEvent.h"

class EventGameEnd : public AEvent
{
private:
  char status_;
  int player_;
  int total_;  

public:
  EventGameEnd();
  virtual ~EventGameEnd();
  void setStatus(char status);
  void setScorePlayer(int j1);
  void setScoreTotal(int total);
  char getStatus() const;
  int getScorePlayer() const;
  int getScoreTotal() const;

};
