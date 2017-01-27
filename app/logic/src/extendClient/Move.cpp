#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"

void ExtendClient::MoveNorth(NetworkPacket& p){
	c->y--;
	if(!getMap(p, c->x-8, c->y-6, c->z, 18, 1)){
		c->disconnect("failed to load map");
		return;
	}
}
void ExtendClient::MoveWest(NetworkPacket& p){
	c->x--;
	if(!getMap(p, c->x-8, c->y-6, c->z, 1, 14)){
		c->disconnect("failed to load map");
		return;
	}
}
void ExtendClient::MoveSouth(NetworkPacket& p){
	c->y++;
	if(!getMap(p, c->x-8, c->y-6, c->z, 18, 1)){
		c->disconnect("failed to load map");
		return;
	}
}
void ExtendClient::MoveEast(NetworkPacket& p){
	c->x++;
	if(!getMap(p, c->x-8, c->y-6, c->z, 1, 14)){
		c->disconnect("failed to load map");
		return;
	}
}
