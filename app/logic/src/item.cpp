#include "item.hpp"
#include "datLoader.hpp"
#include "packet.hpp"
#include "client.hpp"

Item::Item(){
	id = 0;
	itemTemplate = 0;
}

Item::Item(uint32_t _id, DatLoader* dat, NetworkPacket& p, Client* c):
	id(_id)
{
	itemTemplate = dat->getItem(_id);
	if(itemTemplate == 0){
		return;
	}
	if(itemTemplate->stackable || itemTemplate->splash || itemTemplate->fluidContainer || itemTemplate->rune){
		if(p.getSize()<2){
			c->disconnect("Item stack too short");
			return;
		}
		stack = p.getUint8();
	}
}