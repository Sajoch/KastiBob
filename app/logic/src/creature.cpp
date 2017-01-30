#include "creature.hpp"
#include "packet.hpp"
#include <iostream>

using namespace std;

Creature::Creature(){
  id = -1;
  x = y = z = 0;
}

Creature Creature::setNewCreature(NetworkPacket& p){
  Creature ret;
  uint32_t oldId = p.getUint32();
  ret.id = p.getUint32();
  ret.name = p.getTString();
  ret.hpp = p.getUint8();
  uint32_t dir = p.getUint8();
  //sth
  ret.apperance.fromMsg(p);
  
  ret.lightLevel = p.getUint8();
  ret.lightColor = p.getUint8();
  ret.speed = p.getUint16();
  ret.skull = p.getUint8();
  ret.blockSpace = p.getUint8();
  return ret;
}

Creature Creature::setKnownCreature(NetworkPacket& p){
  Creature ret;
  uint32_t unk1 = p.getUint32();
  cout<<"known "<<unk1<<endl;
  exit(1);
  return ret;
}

Creature Creature::setUnk1Creature(NetworkPacket& p){
  Creature ret;
  cout<<"unk1"<<endl;
  exit(1);
  return ret;
}
uint32_t Creature::getX(){
  return x;
}

uint32_t Creature::getY(){
  return y;
}

uint32_t Creature::getZ(){
  return z;
}
