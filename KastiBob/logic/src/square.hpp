#ifndef __SQUARE_HPP
#define __SQUARE_HPP

#include <vector>
#include "creature.hpp"

class Square{
  std::vector<Creature> creatures;
public:
  bool getCreature(uint32_t stackId, Creature& cr);
  bool removeCreature(uint32_t stackId);
  bool addCreature(Creature& v);
};

#endif
