#include "utils.hpp"
#include "ground.hpp"

Square& Ground::getSquare(int32_t x, int32_t y, int32_t z){
  // 2 + 2 + 1
  int32_t idx = (x&0xffff);
  idx <<= 8;
  idx |= (y&0xffff);
  return squares[idx];
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

int Ground::getMap(std::vector<Square> sqs, int32_t x, int32_t y, int32_t z){
  int32_t px, py, mx, my;
  px = x - rangeX;
  py = y - rangeY;
  mx = x + rangeX;
  my = y + rangeY;
  for(;px<mx;px++){
    for(;py<my;py++){
      Square& singleSq = getSquare(px, py, z);
      sqs.push_back(singleSq);
    }
  }
  return 0;
}

bool Ground::moveCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId, int32_t dstX, int32_t dstY, int32_t dstZ){
  Creature obj;
  Square& srcSq = getSquare(srcX, srcY, srcZ);
  Square& dstSq = getSquare(dstX, dstY, dstZ);
  if(!srcSq.getCreature(stackId, obj)){
    DEBUG("move: cannot get creature from old square");
    return false;
  }
  if(!dstSq.addCreature(obj)){
    DEBUG("move: cannot add creature to new square");
    return false;
  }
  if(!srcSq.removeCreature(stackId)){
    DEBUG("move: cannot remove creature from old square");
    return false;
  }
  return true;
}
bool Ground::removeCreature(int32_t srcX, int32_t srcY, int32_t srcZ, int32_t stackId){
  Square& sq = getSquare(srcX, srcY, srcZ);
  if(!sq.removeCreature(stackId)){
    DEBUG("remove: cannot remove creature from square");
    return false;
  }
  return true;
}
Creature* Ground::getCreatureByID(uint32_t id){
  return creatures[id];
}