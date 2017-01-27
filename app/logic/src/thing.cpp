#include "thing.hpp"
#include "item.hpp"
#include "creature.hpp"
#include <iostream>

using namespace std;

Thing::Thing(){
	
}
Thing::Thing(ThingType _type){
	type = _type;
}


Thing Thing::getThing(NetworkPacket& p){
	Thing ret;
	cout<<"thing"<<endl;
	uint32_t type = p.getUint16();
	switch(type){
		case 0x61:
			ret = Creature::setNewCreature(p);
		break;
		case 0x62:
			ret = Creature::setKnownCreature(p);
		break;
		case 0x63:
			ret = Creature::setUnk1Creature(p);
		break;
		default:
			ret = Item(type);
		break;
	}
	return ret;
}

bool Thing::good(){
	return error==0?true:false;
}

void Thing::setError(int a){
	error = a;
}