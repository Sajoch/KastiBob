#ifndef __SQUARE_HPP
#define __SQUARE_HPP

#include <vector>
#include <map>
#include "creature.hpp"
#include "item.hpp"
#include "dll.h"

class API Square{
  friend class Ground;
  int32_t x;
  int32_t y;
  std::map<int32_t, std::vector<Item> > items;
  std::map<int32_t, std::vector<Creature> > creatures;
  Item empty_item;
  Creature empty_creature;
public:
  Square(int32_t _x, int32_t _y);
  bool getCreature(int32_t _z, uint32_t stackId, Creature& cr);
  bool removeCreature(int32_t _z, uint32_t stackId);
  void addCreature(int32_t _z, Creature& v);
  void addItem(int32_t _z, Item& v);
  uint32_t getItemsAmount(int32_t _z);
  Item& getItem(int32_t _z, uint32_t i);
  void clear(int32_t _z);
  int32_t getX();
  int32_t getY();
  void dump();
};

#endif
