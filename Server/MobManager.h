#pragma once

#include <map>
#include <list>
#include <string>
#include "IDlLoader.h"
#include "Pool.h"
#include "AMob.h"

class MobManager
{
private:
  std::list<IDlLoader<AMob> *>                  loader_;
  std::map<std::string, Pool<AMob *> >          mobs_;
  std::map<int, std::vector<std::string> >      levels_;

private:
  MobManager();
  static void   loadMobTypes(std::list<std::string>&);

public:
  MobManager(std::list<Tile*> & t);
  ~MobManager();
  AMob*  Spawn(std::string const& typeName, int x, int y, int angle);
  void  Destroy(AMob * mob);
  const std::map<int, std::vector<std::string> >&  getMobsLevels() const;
};
