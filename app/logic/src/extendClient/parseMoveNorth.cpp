#include "../network.hpp"
#include "../client.hpp"

void ExtendClient::parseMoveNorth(NetworkPacket& p){
	c->y--;
}
