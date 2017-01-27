#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../ground.hpp"

void ExtendClient::CreatureMove(NetworkPacket& p){
	if(p.getSize()<11) {
		c->disconnect("CreatureMove too short");
		return;
	}
	uint16_t old_x = p.getUint16();
	uint16_t old_y = p.getUint16();
	uint16_t old_z = p.getUint8();
	uint16_t old_stackPos = p.getUint8();
	uint16_t new_x = p.getUint16();
	uint16_t new_y = p.getUint16();
	uint16_t new_z = p.getUint8();
	c->gMap->moveCreature(old_x, old_y, old_z, old_stackPos, new_x, new_y, new_z);
}
void ExtendClient::CreatureHealth(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("CreatureHealth too short");
		return;
	}
}
void ExtendClient::CreatureLight(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("CreatureLight too short");
		return;
	}
	uint32_t id = p.getUint32();
	uint8_t level, color;
	level = p.getUint8();
	color = p.getUint8();
	Creature* cr = c->gMap->getCreatureByID(id);
	if(cr != 0){
		cr->lightLevel = level;
		cr->lightColor = color;
	}
}
void ExtendClient::CreatureSpeak(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("CreatureSpeak too short");
		return;
	}
}