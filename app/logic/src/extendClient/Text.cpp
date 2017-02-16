#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include <iostream>

void ExtendClient::TextMessage(NetworkPacket& p){
	if(p.getSize()<1){
		c->disconnect("TextMessage too short");
		return;
	}
	uint16_t type = p.getUint8();
	if(p.getSize()<2 && p.getSize()<(p.peakTStringSize()+2)){
		c->disconnect("TextMessage too short");
		return;
	}
	std::string msg = p.getTString();
<<<<<<< HEAD
	std::cout<<"text type: "<<type<<": "<<msg<<std::endl;
=======
	std::cout<<"type: "<<type<<": "<<msg<<std::endl;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}
