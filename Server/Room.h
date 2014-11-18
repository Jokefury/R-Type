
#pragma once

#include        <list>
#include        "User.h"

class   Room
{
private:
  int                           id_;
  std::list<const User*>        clients_;
  bool                          running_;
  int                           config_;
  unsigned int                  nbReady_;
  std::list<int> &              ready_;
  std::pair<short, short>       ports_;

public:
  Room(int, int, std::list<int>&);
  ~Room();
  bool	pushClient(const User *);
  bool  popClient(const User *);
  const std::list<const User*> &	getClients() const;
  bool	setRunning();
  bool	isRunning() const;
  int	getId() const;
  int	getNbPlayers() const;
  void	newPlayerReady();
  short	getSendPort() const;
  short getReceivePort() const;
  int	getNbReady() const;

private:
  static short    port_;
};
