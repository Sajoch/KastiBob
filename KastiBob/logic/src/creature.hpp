#ifndef __CREATURE_HPP
#define __CREATURE_HPP

#include <string>
#include "utils.hpp"
#include "outfit.hpp"

enum class CreatureType{
  Other,
  Mob,
  Npc,
  Hero
};

class Creature{
friend class Client;
  CreatureType type;
  std::string name;
  uint32_t id;
  uint32_t x;
  uint32_t y;
  uint32_t z;
  Outfit apperance;
  ClientDirectory directory;
  
};

#endif
