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
<<<<<<< HEAD
  static int setNewCreature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
  static int setKnownCreature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
  static int setUnk1Creature(class DatLoader* datobjs, Creature & ret, NetworkPacket& p);
=======
  static Creature setNewCreature(NetworkPacket& p);
  static Creature setKnownCreature(NetworkPacket& p);
  static Creature setUnk1Creature(NetworkPacket& p);
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  uint32_t getX();
  uint32_t getY();
  uint32_t getZ();
  class DatObject* getTemplate();
  Outfit& getApperance();
};

#endif
