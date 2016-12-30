#include "square.hpp"


bool Square::getCreature(uint32_t stackId, Creature& cr){
  if(stackId < creatures.size()){
    cr = creatures[stackId];
    return true;
  }else{
    return false;
  }
}
bool Square::removeCreature(uint32_t stackId){
  if(stackId < creatures.size()){
    creatures.erase(creatures.begin() + stackId);
    return true;
  }else{
    return false;
  }
}
bool Square::addCreature(Creature& v){
  creatures.push_back(v);
  return true;
}