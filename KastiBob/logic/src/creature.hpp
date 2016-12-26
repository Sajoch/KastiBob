#ifndef __CREATURE_HPP
#define __CREATURE_HPP

#include <string>

enum class CreatureType{
  Other,
  Mob,
  Npc
};

class Creature{
  CreatureType type;
  std::string name;
};

#endif
