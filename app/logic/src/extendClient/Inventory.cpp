#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"

void ExtendClient::InventorySetSlot(NetworkPacket& p){
	if(p.getSize()<4){
		c->disconnect("InventorySetSlot too short");
		return;
	}
	uint16_t slotId = p.getUint8();
	uint16_t itemId = p.getUint16();
	uint16_t attr = p.getUint8();
	
}
void ExtendClient::InventoryResetSlot(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("InventoryResetSlot too short");
		return;
	}
	int32_t slotId = p.getUint8();
	
}