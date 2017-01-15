#include "../network.hpp"
#include "../client.hpp"

void ExtendClient::parseMoveWest(NetworkPacket& p){
	c->x--;
}
