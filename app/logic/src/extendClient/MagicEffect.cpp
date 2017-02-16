#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
<<<<<<< HEAD
#include <iostream>
=======
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa

void ExtendClient::MagicEffect(NetworkPacket& p){
	if(p.getSize()<6){
		c->disconnect("MagicEffect too short");
		return;
	}
<<<<<<< HEAD
	uint32_t x, y, z, type;
=======
	int32_t x, y, z, type;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	type = p.getUint8();
<<<<<<< HEAD
	std::cout<<"magic effect "<<type<<std::endl;
=======
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}