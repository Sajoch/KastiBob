#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../ground.hpp"

void ExtendClient::WorldLight(NetworkPacket& p){
	if(p.getSize()<2){
		c->disconnect("WorldLight too short");
		return;
	}
	uint8_t level, color;
	level = p.getUint8();
	color = p.getUint8();
	c->gMap->parseLight(level, color);	
}