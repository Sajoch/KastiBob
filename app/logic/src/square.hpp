#ifndef __SQUARE_HPP
#define __SQUARE_HPP

#include <vector>
#include "creature.hpp"
#include "item.hpp"

class Square{
  friend class Ground;
  int32_t x;
  int32_t y;
  int32_t z;
  std::vector<Item> items;
  std::vector<Creature> creatures;
public:
  Square(int32_t _x, int32_t _y, int32_t _z);
  bool getGround(Item& it);
  bool getCreature(uint32_t stackId, Creature& cr);
  bool removeCreature(uint32_t stackId);
  void addCreature(Creature& v);
  void addItem(Item& v);
  void clear();
};

#endif
