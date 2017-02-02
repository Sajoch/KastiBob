#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../item.hpp"
#include "../square.hpp"
#include "../ground.hpp"

void ExtendClient::TileAddThing(NetworkPacket& p){
	if(p.getSize()<8){
		c->disconnect("TileAddThing too short");
		return;
	}
	uint16_t x, y;
	uint8_t z, stack;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	Square& sq = c->gMap->getSquare(x, y, z);
	stack = p.getUint8();
	int32_t vAttr = p.getUint16();
	Creature cr;
	Item it;
	switch(vAttr){
		case 0x61:
			cr = Creature::setNewCreature(p);
			sq.addCreature(cr);
		break;
		case 0x62:
			cr = Creature::setKnownCreature(p);
		break;
		case 0x63:
			cr = Creature::setUnk1Creature(p);
		break;
		default:
			it = Item(vAttr, c->datobjs, p, c);
			sq.addItem(it);
		break;
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