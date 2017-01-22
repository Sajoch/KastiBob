#ifndef __OUTFIT__HPP
#define __OUTFIT__HPP

#include <cinttypes>

class Outfit{
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
  bool fromMsg(class NetworkPacket* p);
  void toMsg(class NetworkPacket* p);
};

#endif
