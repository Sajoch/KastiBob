#ifndef __OUTFIT__HPP
#define __OUTFIT__HPP

#include <cinttypes>
#include "dll.h"

class API Outfit{
  static uint32_t colorP[33*4+1];
  uint16_t lookType;
  uint8_t lookHead;
  uint8_t lookBody;
  uint8_t lookLegs;
  uint8_t lookFeet;
  uint8_t lookAddons;
  //TODO looktypeex (item)
  uint16_t lookMount;
public:
  Outfit();
  bool fromMsg(class NetworkPacket& p);
  void toMsg(class NetworkPacket& p);
  uint16_t getType();
  uint32_t getHeadColor();
  uint32_t getBodyColor();
  uint32_t getLegsColor();
  uint32_t getFeetColor();
};

#endif
