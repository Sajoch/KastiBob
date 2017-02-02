#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include <iostream>

void ExtendClient::MagicEffect(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("MagicEffect too short");
		return;
	}
	uint32_t x, y, z, type;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	type = p.getUint8();
	std::cout<<"magic effect "<<type<<std::endl;
}