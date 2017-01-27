#ifndef __SQUARE_HPP
#define __SQUARE_HPP

#include <vector>
#include "creature.hpp"
#include "item.hpp"

class Square{
  std::vector<Item> items;
  std::vector<Creature> creatures;
public:
  bool getCreature(uint32_t stackId, Creature& cr);
  bool removeCreature(uint32_t stackId);
  void addCreature(Creature& v);
  void addItem(Item& v);
  void clear();
};

#endif
