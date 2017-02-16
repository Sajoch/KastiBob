#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../item.hpp"

void ExtendClient::InventorySetSlot(NetworkPacket& p){
	if(p.getSize()<3){
		c->disconnect("InventorySetSlot too short");
		return;
	}
	uint16_t slotId = p.getUint8();
	Item it = Item(p.getUint16(), c->datobjs, p, c);
}
void ExtendClient::InventoryResetSlot(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("InventoryResetSlot too short");
		return;
	}
	int32_t slotId = p.getUint8();
	
}