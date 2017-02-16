#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
<<<<<<< HEAD
#include "../ground.hpp"

void ExtendClient::MoveNorth(NetworkPacket& p){
	c->y--;
	if(!getMap(p, c->x-8, c->y-6, c->z, 18, 1)){
		c->disconnect("failed to load map");
		return;
	}
	MoveCheckZ();
}
void ExtendClient::MoveWest(NetworkPacket& p){
	c->x--;
	if(!getMap(p, c->x-8, c->y-6, c->z, 1, 14)){
		c->disconnect("failed to load map");
		return;
	}
	MoveCheckZ();
}
void ExtendClient::MoveSouth(NetworkPacket& p){
	c->y++;
	if(!getMap(p, c->x-8, c->y-6, c->z, 18, 1)){
		c->disconnect("failed to load map");
		return;
	}
	MoveCheckZ();
}
void ExtendClient::MoveEast(NetworkPacket& p){
	c->x++;
	if(!getMap(p, c->x-8, c->y-6, c->z, 1, 14)){
		c->disconnect("failed to load map");
		return;
	}
	MoveCheckZ();
}

void ExtendClient::MoveCheckZ(){
	if(c->z > 7){
		c->under = true;
		return;
	}
	Square& sq = c->gMap->getSquare(c->x, c->y);
	if(sq.isAbove(c->z)){
		c->under = true;
		return;
	}
	c->under = false;
}
=======

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
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
