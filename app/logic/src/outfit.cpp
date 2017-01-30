#include "outfit.hpp"
#include "packet.hpp"
#include <iostream>

using namespace std;

Outfit::Outfit(){

}

bool Outfit::fromMsg(NetworkPacket& p){
  if(p.getSize()<2) return false;
  lookType = p.getUint16();
  if(lookType != 0){
    if(p.getSize()<5) return false;
    lookHead = p.getUint8();
    lookBody = p.getUint8();
    lookLegs = p.getUint8();
    lookFeet = p.getUint8();
    lookAddons = p.getUint8();
  } else {
    if(p.getSize()<2) return false;
    uint16_t itemId = p.getUint16();
    if(itemId != 0){ //TODO looktypeex
      cout<<"looktypeex"<<endl;
      return false;
    }
  }
  if(p.getSize()<2) return false;
  lookMount = p.getUint16();
  return true;
}

void Outfit::toMsg(NetworkPacket& p){
  //TODO finish
}
