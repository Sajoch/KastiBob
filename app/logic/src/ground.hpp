#ifndef __GROUND_HPP
#define __GROUND_HPP

#include <map>
#include <vector>
#include "square.hpp"

class Ground{
  bool initialized;
  int32_t rangeX;
  int32_t rangeY;
  uint16_t lightLevel;
  uint16_t lightColor;
  std::map<int64_t, Square> squares;
  std::map<uint32_t, Creature*> creatures; 
public:
  Ground();
  void set(int32_t rx, int32_t ry);
  bool parseMap();
  bool parseLight(uint16_t lvl, uint16_t color);
  int getMap(std::vector<Square> sqs, int32_t x, int32_t y, int32_t z);
  bool moveCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId, int32_t dstX, int32_t dstY, int32_t dstZ);
  bool removeCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId);
  Square& getSquare(int32_t x, int32_t y, int32_t z);
  Creature* getCreatureByID(uint32_t id);
  bool isInitialized();
};

#endif
