#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../item.hpp"
#include "../square.hpp"
#include "../ground.hpp"
#include <iostream>

using	namespace std;

void ExtendClient::TileAddThing(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("TileAddThing too short");
		return;
	}
	uint16_t x, y;
	uint8_t z, stack;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	stack = p.getUint8();
	Square& sq = c->gMap->getSquare(x, y);
	int getThing_ret = getThing(sq, z, p);
	if(getThing_ret != 0){
		c->disconnect("getThing from TileAddThing");
	}
}

void ExtendClient::TileUpdateItem(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("TileUpdateItem too short");
		return;
	}
	uint16_t x, y;
	uint8_t z, stack;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	stack = p.getUint8();
	Square& sq = c->gMap->getSquare(x, y);
	int getThing_ret = getThing(sq, z, p);
	if(getThing_ret != 0){
		c->disconnect("getThing from TileUpdateItem");
	}
}

void ExtendClient::TileRemoveThing(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("TileRemoveThing too short");
		return;
	}
	uint16_t x, y;
	uint8_t z, stack;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	stack = p.getUint8();
}

int ExtendClient::getThing(Square& sq, int32_t _z, NetworkPacket& p){
	if(p.getSize()<2){
		c->disconnect("getThing too short");
		return 127;
	}
	int32_t vAttr = (int16_t)p.getUint16();
	//cout<<"thing "<<vAttr<<endl;
	Creature cr;
	Item it;
	int ret;
	switch(vAttr){
		case 0x61:
			ret = Creature::setNewCreature(c->datobjs, cr, p);
			if(ret != 0){
				return ret;
			}
			sq.addCreature(_z, cr);
		break;
		case 0x62:
			ret = Creature::setKnownCreature(c->datobjs, cr, p);
			if(ret != 0){
				return ret;
			}
			sq.addCreature(_z, cr);
		break;
		case 0x63:
			ret = Creature::setUnk1Creature(c->datobjs, cr, p);
			if(ret != 0){
				return ret;
			}
			sq.addCreature(_z, cr);
		break;
		default:
			it = Item(vAttr, c->datobjs, p, c);
			sq.addItem(_z, it);
		break;
	}
	return 0;
}