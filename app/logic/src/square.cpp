#include "square.hpp"
#include "datLoader.hpp"


Square::Square(int32_t _x, int32_t _y, int32_t _z):
x(_x), y(_y), z(_z)
{
  
}

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
void Square::addCreature(Creature& v){
  creatures.push_back(v);
}
void Square::addItem(Item& v){
  items.push_back(v);
}
void Square::clear(){
  items.clear();
  creatures.clear();
}
bool Square::getGround(Item& it){
  for(size_t i=0;i<items.size();i++){
    DatObject* o = items[i].itemTemplate;
    if(o != 0){
      if(o->ground){
        it = items[i];
        return true;
      }
    }
  }
  return false;
}