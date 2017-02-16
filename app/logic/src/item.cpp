#include "item.hpp"
<<<<<<< HEAD
#include "datLoader.hpp"
#include "packet.hpp"
#include "client.hpp"

Item::Item(){
	id = 0;
	itemTemplate = 0;
}

Item::Item(int32_t _id, DatLoader* dat, NetworkPacket& p, Client* c):
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

int32_t Item::getId(){
	return id;
}
DatObject* Item::getTemplate(){
	return itemTemplate;
=======

Item::Item(uint32_t _id):
	Thing(ThingType::ITEM), id(_id)
{
	setError(0);
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}