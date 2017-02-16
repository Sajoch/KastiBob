#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"

void ExtendClient::PlayerStats(NetworkPacket& p){
	if(p.getSize()<24){
		c->disconnect("PlayerStats too short");
		return;
	}
	c->health = p.getUint16();
	c->max_health = p.getUint16();
	c->free_cap = p.getUint32();
	c->experience = p.getUint32();
	c->level = p.getUint16();
	c->percent_level = p.getUint8();
	c->mana = p.getUint16();
	c->max_mana = p.getUint16();
	c->magic_level = p.getUint8();
	c->magic_level_percent = p.getUint8();
	c->soul = p.getUint8();
	c->stamina = p.getUint16();
}

void ExtendClient::PlayerSkills(NetworkPacket& p){
	if(p.getSize()<14){
		c->disconnect("PlayerSkills too short");
		return;
	}
	c->skills[0].val = p.getUint8();
	c->skills[0].percent = p.getUint8();
	
	c->skills[1].val = p.getUint8();
	c->skills[1].percent = p.getUint8();
	
	c->skills[2].val = p.getUint8();
	c->skills[2].percent = p.getUint8();
	
	c->skills[3].val = p.getUint8();
	c->skills[3].percent = p.getUint8();
	
	c->skills[4].val = p.getUint8();
	c->skills[4].percent = p.getUint8();
	
	c->skills[5].val = p.getUint8();
	c->skills[5].percent = p.getUint8();
	
	c->skills[6].val = p.getUint8();
	c->skills[6].percent = p.getUint8();
}

void ExtendClient::PlayerIcons(NetworkPacket& p){
	if(p.getSize()<2){
		c->disconnect("PlayerIcons too short");
		return;
	}
	c->icons = p.getUint16();
}

void ExtendClient::PlayerCancelWalk(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("PlayerCancelWalk too short");
		return;
	}
	uint16_t dir = p.getUint8();
}
