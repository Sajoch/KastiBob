#ifndef __CREATURE_HPP
#define __CREATURE_HPP

#include <string>
#include "utils.hpp"
#include "outfit.hpp"
#include "thing.hpp"
#include "dll.h"

enum class CreatureType{
  Other,
  Mob,
  Npc,
  Hero
};

class API Creature: public Thing{
friend class Client;
friend class ExtendClient;
  CreatureType type;
  std::string name;
  uint32_t id;
  uint32_t x;
  uint32_t y;
  uint32_t z;
  uint32_t hpp;
  uint32_t lightLevel;
  uint32_t lightColor;
  uint32_t speed;
  uint32_t skull;
  bool blockSpace;
  Outfit apperance;
  ClientDirectory directory;
public:
  Creature();
  static Creature setNewCreature(NetworkPacket& p);
  static Creature setKnownCreature(NetworkPacket& p);
  static Creature setUnk1Creature(NetworkPacket& p);
  uint32_t getX();
  uint32_t getY();
  uint32_t getZ();
};

#endif
