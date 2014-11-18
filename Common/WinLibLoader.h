
#ifndef __LIBLOADER_H__
# define __LIBLOADER_H__
#include <Windows.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include "IDlLoader.h"
#include <list>

template<typename T>
class LibLoader : public IDlLoader<T>
{
private:
	typedef T* (*Dll_func)(int id, std::list<Tile*> & t);
	HMODULE _handle;
	std::string _libName;

public:
	LibLoader(const std::string& libName) : _libName(libName)
	{
		_libName.append (".dll");
		if (!(this->_handle = LoadLibrary(this->_libName.c_str())))
			throw std::runtime_error("Error while opening " + this->_libName);
	}

	~LibLoader(void)
	{
		FreeLibrary(this->_handle);
	}

	T* getInstance(const std::string& sym, int id, std::list<Tile*> & t)
	{
		Dll_func func = reinterpret_cast<Dll_func>(GetProcAddress(this->_handle, sym.c_str()));
		if (!func)
			throw std::runtime_error("Error while loading " + this->_libName);
		return (func(id, t));
	}
};

#endif /* !__LIBLOADER_H__*/
