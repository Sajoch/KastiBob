#include "../extendClient.hpp"
#include "../client.hpp"
#include "../network.hpp"
#include "../packets/PingPacket.hpp"

void ExtendClient::Ping(NetworkPacket& p){
	c->conn->addPacket(PingPacket(c->xtea));
}
