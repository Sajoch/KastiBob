#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../item.hpp"

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
	stack = p.getUint8();
	Item it = Item(p.getUint16(), c->datobjs, p, c);
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