#include "utils.hpp"
#include "ground.hpp"


Square& Ground::getSquare(int32_t x, int32_t y){
  size_t s = squares.size();
  for(size_t i=0;i<s;i++){
    Square& sq = squares[i];
    if(sq.x == x && sq.y == y){
      return sq;
    }
  }
  squares.push_back(Square(x, y));
  return squares.back();
}
Ground::Ground(){
  initialized = false;
  rangeX = 0;
  rangeY = 0;
}
void Ground::set(int32_t rx, int32_t ry){
  initialized = true;
  rangeX = rx;
  rangeY = ry;
}
bool Ground::isInitialized(){
  return initialized;
}

bool Ground::parseMap(){
  return false;
}

bool Ground::parseLight(uint16_t lvl, uint16_t color){
  lightLevel = lvl;
  lightColor = color;
  return true;
}

bool Ground::moveCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId, int32_t dstX, int32_t dstY, int32_t dstZ){
  Creature obj;
  Square& srcSq = getSquare(srcX, srcY);
  Square& dstSq = getSquare(dstX, dstY);
  if(!srcSq.getCreature(srcZ, stackId, obj)){
    DEBUG("move: cannot get creature from old square");
    return false;
  }
  dstSq.addCreature(dstZ, obj);
  
  if(!srcSq.removeCreature(srcZ, stackId)){
    DEBUG("move: cannot remove creature from old square");
    return false;
  }
  return true;
}
bool Ground::removeCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId){
  Square& sq = getSquare(srcX, srcY);
  if(!sq.removeCreature(srcZ, stackId)){
    DEBUG("remove: cannot remove creature from square");
    return false;
  }
  return true;
}
Creature* Ground::getCreatureByID(uint32_t id){
  return creatures[id];
}