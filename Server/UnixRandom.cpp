
#include "Random.h"

void Random::init(unsigned int speed)
{
  srandom(speed);
}

int Random::gen()
{
  return random();
}
