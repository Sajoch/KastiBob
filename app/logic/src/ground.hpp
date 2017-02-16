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
<<<<<<< HEAD
  std::vector<Square> squares;
=======
  std::map<int32_t, Square> squares;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  std::map<uint32_t, Creature*> creatures; 
public:
  Ground();
  void set(int32_t rx, int32_t ry);
  bool parseMap();
  bool parseLight(uint16_t lvl, uint16_t color);
  bool moveCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId, int32_t dstX, int32_t dstY, int32_t dstZ);
  bool removeCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId);
<<<<<<< HEAD
  Square& getSquare(int32_t x, int32_t y);
=======
  Square& getSquare(int32_t x, int32_t y, int32_t z);
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  Creature* getCreatureByID(uint32_t id);
  bool isInitialized();
};

#endif
