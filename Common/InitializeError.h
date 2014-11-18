
#pragma once

#include <string>

class InitializeError : public std::exception
{
  std::string info;

public:

  InitializeError(std::string w) : info(w) {}
  virtual ~InitializeError() throw() {}
  virtual  const char * what () const throw() {return info.c_str ();}
};
