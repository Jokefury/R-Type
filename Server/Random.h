
#pragma once

#include <cstdlib>

class Random
{
 public:
  static void init(unsigned int speed);
  static int gen();
};
