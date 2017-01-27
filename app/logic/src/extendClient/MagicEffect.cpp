#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"

void ExtendClient::MagicEffect(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("MagicEffect too short");
		return;
	}
	int32_t x, y, z, type;
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	type = p.getUint8();
}