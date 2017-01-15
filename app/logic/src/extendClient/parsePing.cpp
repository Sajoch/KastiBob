#include "../network.hpp"
#include "../client.hpp"
#include "../packets/PingPacket.hpp"

void ExtendClient::parsePing(NetworkPacket& p){
	c->conn->addPacket(PingPacket(c->xtea));
}
