#include "creature.hpp"
#include "packet.hpp"
#include "datLoader.hpp"
#include <iostream>

using namespace std;

Creature::Creature(){
  id = -1;
  x = y = z = 0;
  creatureTemplate = 0;
}

int Creature::setNewCreature(DatLoader* datobjs, Creature & ret, NetworkPacket& p){
  if(p.getSize()<8){
    return 1;
  }
  uint32_t oldId = p.getUint32();
  ret.id = p.getUint32();
  if(!p.peakStringLength()){
    return 2;
  }
  ret.name = p.getTString();
  if(p.getSize()<2){
    return 3;
  }
  ret.hpp = p.getUint8();
  uint32_t dir = p.getUint8();
  //sth
  if(!ret.apperance.fromMsg(p)){
    return 5;
  }
  cout<<"creature outfit "<<ret.apperance.getType()<<endl;
  ret.creatureTemplate = datobjs->getOutfit(ret.apperance.getType());
  if(p.getSize()<6){
    return 4;
  }
  ret.lightLevel = p.getUint8();
  ret.lightColor = p.getUint8();
  ret.speed = p.getUint16();
  ret.skull = p.getUint8();
  ret.blockSpace = p.getUint8();
  return 0;
}

int Creature::setKnownCreature(DatLoader* datobjs, Creature & ret, NetworkPacket& p){
  cout<<"known"<<endl;
  if(p.getSize()<6){
    return 1;
  }
  ret.id = p.getUint32();
  ret.hpp = p.getUint8();
  uint32_t dir = p.getUint8();
  //sth
  if(!ret.apperance.fromMsg(p)){
    return 3;
  }
  cout<<"creature outfit "<<ret.apperance.getType()<<endl;
  ret.creatureTemplate = datobjs->getOutfit(ret.apperance.getType());
  if(p.getSize()<6){
    return 2;
  }
  ret.lightLevel = p.getUint8();
  ret.lightColor = p.getUint8();
  ret.speed = p.getUint16();
  ret.skull = p.getUint8();
  ret.blockSpace = p.getUint8();
  cout<<"stop known"<<endl;
  return 0;
}

int Creature::setUnk1Creature(DatLoader* datobjs, Creature& ret, NetworkPacket& p){
  cout<<"unk1"<<endl;
  exit(1);
  return 0;
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

DatObject* Creature::getTemplate(){
  return creatureTemplate;
}
Outfit& Creature::getApperance(){
  return apperance;
}