
#ifndef __UNIXLIBLOADER_H__
#define __UNIXLIBLOADER_H__

#include <dlfcn.h>
#include <string>
#include <stdexcept>
#include <list>
#include "IDlLoader.h"

template<typename T>
class   LibLoader : public IDlLoader<T>
{
private:
  typedef T*    (*Dll_func)(int id, std::list<Tile*> & t);
  void          *_handle;
  std::string   _libName;

public:
  LibLoader(const std::string& libName) : _libName(libName)
  {
    _libName = "../Mobs/bin/" + _libName + ".so";
    if (!(this->_handle = dlopen(this->_libName.c_str(), RTLD_LAZY)))
	throw std::runtime_error("Error while opening " + this->_libName);
  }

  ~LibLoader(void)
  {
    dlclose(this->_handle);
  }

  T*    getInstance(const std::string& sym, int id, std::list<Tile*> & t)
  {
    Dll_func func = reinterpret_cast<Dll_func>(dlsym(this->_handle, sym.c_str()));

    if (!func)
      throw std::runtime_error("Error while loading " + this->_libName);
    return (func(id, t));
  }
};

#endif
