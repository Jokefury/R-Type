#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include "Bydo.h"
#include "MobManager.h"

#if defined(_WIN32) || defined(_WIN64)
#include        "WinLibLoader.h"
#elif UNIX
#include        "UnixLibLoader.h"
#endif

MobManager::MobManager(std::list<Tile*> & t)
{
  std::list<std::string>                mobTypes;
  std::list<std::string>::iterator      it;
  int                                   id;
  int                                   i;
  IDlLoader<AMob> *                     tmp;
  AMob                                  *mob;

  id = 100;
  loadMobTypes (mobTypes);
  for (it = mobTypes.begin (); it != mobTypes.end (); ++it)
    {
      try
        {
          tmp = new LibLoader<AMob>(*it);
          if (tmp)
            {
              this->loader_.push_front (tmp);
              for (i = -1; i < 19; ++i)
                {
                  this->mobs_[*it].pushElement(tmp->getInstance("entryPoint", id, t));
                  ++id;
                }
              mob = tmp->getInstance("entryPoint", id, t);
              levels_[mob->getLevel ()].push_back (*it);
              mobs_[*it].pushElement (mob);
            }
        }
      catch (std::runtime_error & e)
        {}
    }
  for (i = -1; i < 20; ++i, ++id)
    this->mobs_["Bydo"].pushElement(new Bydo (id, t));
  levels_[1].push_back ("Bydo");
}

MobManager::~MobManager()
{
}

void    MobManager::loadMobTypes(std::list<std::string>& m)
{
  std::fstream  f;
  std::string   line;

  f.open ("../Mobs/conf");
  if (!f.is_open ())
    return;
  while (f.good ())
    {
      std::getline (f, line);
      m.push_back (line);
    }
}

AMob*    MobManager::Spawn(std::string const& typeName, int x, int y, int angle)
{
  AMob*         tmp;

  tmp = this->mobs_[typeName].getElement();
  if (!tmp)
    return 0;
  tmp->reInit(x, y, angle);
  return tmp;
}

void    MobManager::Destroy(AMob * mob)
{
  if (mob)
    this->mobs_[mob->getName()].pushElement(mob);
}

const std::map<int, std::vector<std::string> >&  MobManager::getMobsLevels() const
{
  return levels_;
}
