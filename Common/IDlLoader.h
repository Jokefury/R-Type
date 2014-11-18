#ifndef __IDLLOADER_H__
# define __IDLLOADER_H__

#include <string>
#include <list>
#include "../Server/Tile.h"

template<typename T>
class IDlLoader
{
public:
	virtual ~IDlLoader() {}
	virtual T* getInstance(const std::string&, int id, std::list<Tile*> & t) = 0;
};

#else

template<typename T>
class IDlLoader;

#endif /* !__IDLLOADER_H__ */
