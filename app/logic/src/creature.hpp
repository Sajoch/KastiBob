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
friend class ExtendClient;
  CreatureType type;
  std::string name;
  uint32_t id;
  int32_t x;
  int32_t y;
  int32_t z;
  uint32_t hpp;
  uint32_t lightLevel;
  uint32_t lightColor;
  uint32_t speed;
  uint32_t skull;
  bool blockSpace;
  Outfit apperance;
  ClientDirectory directory;
  class DatObject* creatureTemplate;
public:
  Creature();
  static int setNewCreature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
  static int setKnownCreature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
  static int setUnk1Creature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
  uint32_t getX();
  uint32_t getY();
  uint32_t getZ();
  class DatObject* getTemplate();
  Outfit& getApperance();
};

#endif
