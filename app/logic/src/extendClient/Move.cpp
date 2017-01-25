#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"

void ExtendClient::MoveNorth(NetworkPacket& p){
	c->y--;
}
void ExtendClient::MoveWest(NetworkPacket& p){
	c->x--;
}
void ExtendClient::MoveSouth(NetworkPacket& p){
	c->y++;
}
void ExtendClient::MoveEast(NetworkPacket& p){
		c->x++;
}
