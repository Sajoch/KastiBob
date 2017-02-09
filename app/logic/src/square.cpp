#include "square.hpp"
#include "datLoader.hpp"
#include <iostream>

using namespace std;

Square::Square(int32_t _x, int32_t _y):
x(_x), y(_y)
{
  
}

bool Square::getCreature(int32_t _z, uint32_t stackId, Creature& cr){
  if(stackId < creatures[_z].size()){
    cr = creatures[_z][stackId];
    return true;
  }else{
    return false;
  }
}
bool Square::removeCreature(int32_t _z, uint32_t stackId){
  if(stackId < creatures[_z].size()){
    creatures[_z].erase(creatures[_z].begin() + stackId);
    return true;
  }else{
    return false;
  }
}
void Square::addCreature(int32_t _z, Creature& v){
  creatures[_z].push_back(v);
}
void Square::addItem(int32_t _z, Item& v){
  cout<<"add to "<<_z<<endl;
  items[_z].push_back(v);
}
void Square::clear(int32_t _z){
  items[_z].clear();
  creatures[_z].clear();
}
uint32_t Square::getItemsAmount(int32_t _z){
  return items[_z].size();
}
Item& Square::getItem(int32_t _z, uint32_t i){
  uint32_t mi = getItemsAmount(_z);
  if(mi > i){
    return items[_z][i];
  }
  return empty_item;
}
void Square::dump(){
  cout<<"sq "<<x<<","<<y<<endl;
}