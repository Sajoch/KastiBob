#include "../network.hpp"
#include "../client.hpp"

void ExtendClient::parseSelfAppear(NetworkPacket& p){
	if(p.getSize()<7){
		c->disconnect("selfAppear too short");
		return;
	}
	c->id = p.getUint32();
	c->drawSpeed = p.getUint16();

	c->canReportBugs = p.getUint8()==1?true:false;
}