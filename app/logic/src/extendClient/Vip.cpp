#include "../extendClient.hpp"
#include "../client.hpp"
#include "../network.hpp"

void ExtendClient::VipState(NetworkPacket& p){
	if(p.getSize()<4){
		c->disconnect("VipState too short");
		return;
	}
	uint32_t uid = p.getUint32();
	if(!p.peakStringLength()){
		c->disconnect("VipState too short");
		return;
	}
	std::string nick = p.getTString();
	if(p.getSize()<1){
		c->disconnect("VipState too short");
		return;
	}
	uint8_t online = p.getUint8();
}