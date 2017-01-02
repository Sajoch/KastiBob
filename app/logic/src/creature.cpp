#include "creature.hpp"

Creature::Creature(){
  id = -1;
  x = y = z = 0;
}

uint32_t Creature::getX(){
  return x;
}

uint32_t Creature::getY(){
  return y;
}

uint32_t Creature::getZ(){
  return z;
}
