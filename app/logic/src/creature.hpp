#ifndef __CREATURE_HPP
#define __CREATURE_HPP

#include <string>
#include "utils.hpp"
#include "outfit.hpp"
#include "dll.h"

enum class CreatureType{
  Other,
  Mob,
  Npc,
  Hero
};

class API Creature{
friend class Client;
  CreatureType type;
  std::string name;
  uint32_t id;
  uint32_t x;
  uint32_t y;
  uint32_t z;
  Outfit apperance;
  ClientDirectory directory;
public:
  Creature();
  uint32_t getX();
  uint32_t getY();
  uint32_t getZ();
};

#endif
