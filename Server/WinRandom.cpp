
#include "Random.h"

void Random::init(unsigned int speed)
{
  srand(speed);
}

int Random::gen()
{
  return rand();
}
