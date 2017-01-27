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
	std::cout<<"type: "<<type<<": "<<msg<<std::endl;
}
