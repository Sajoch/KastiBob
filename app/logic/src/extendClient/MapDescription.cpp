#include "../extendClient.hpp"
#include "../packet.hpp"
#include "../client.hpp"
#include "../ground.hpp"
//TODO del iostream - only tests
#include <iostream>
using namespace std;
void ExtendClient::MapDescription(NetworkPacket& p){
	if(p.getSize() < 5) {
		c->disconnect("map description too short");
		return;
	}
	c->x = (int16_t)p.getUint16();
	c->y = (int16_t)p.getUint16();
	c->z = (int8_t)p.getUint8();
	c->gMap->set(c->mapViewX, c->mapViewY);
	if(!getMap(p, c->x-8, c->y-6, c->z, 18, 14)){
		c->disconnect("failed to load map");
		return;
	}
	MoveCheckZ();
	//cout<<"hero "<<c->x<<","<<c->y<<","<<c->z<<endl;
}

bool ExtendClient::getMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t bz, int32_t w, int32_t h){
	int32_t currZ, skipTiles;
	skipTiles = 0;
	if(bz > 7){
		int32_t endZ = bz + 2;
		if(endZ > c->mapLayers){
			endZ = c->mapLayers;
		}
		for(currZ = bz - 2; currZ < endZ; currZ++){
			if(!getFloorMap(p, bx, by, currZ, w, h, skipTiles)){
				//cout<<"e6"<<endl;
				return false;
			}
		}
	}else{
		for(currZ = 7; currZ >= 0; currZ--){
			if(!getFloorMap(p, bx, by, currZ, w, h, skipTiles)){
				//cout<<"e4"<<endl;
				return false;
			}
		}
	}
	cout<<"now edited"<<endl;
	c->editedMap = true;
	return true;
}
bool ExtendClient::getFloorMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t _z, int32_t w, int32_t h, int32_t& skipTiles){
	//cout<<"getFloorMap "<<_z<<endl;
	int32_t cx, cy, vAttr;
	for(cx = 0; cx < w; cx++)
		for(cy = 0; cy < h; cy++){
			if(skipTiles == 0){
				if(p.getSize() < 2) {
					cout<<"e2"<<endl;
					return false;
				}
				vAttr = p.peekUint16();
				if(vAttr >= 0xFF00){
					p.getUint16();
					skipTiles = vAttr & 0xFF;
				}else{
					if(!getSquareMap(p, bx + cx, by + cy, _z)){
						cout<<"e1"<<endl;
						return false;
					}
					if(p.getSize() < 2) {
						cout<<"e12"<<endl;
						return false;
					}
					vAttr = p.getUint16();
					skipTiles = vAttr & 0xFF;
				}
			}else{
				skipTiles--;
			}
		}
	
	return true;
}
bool ExtendClient::getSquareMap(NetworkPacket& p, int32_t _x, int32_t _y, int32_t _z){
	//cout<<"getSquareMap "<<_x<<","<<_y<<","<<_z<<endl;
	int32_t vAttr, thingsId;
	Square& sq = c->gMap->getSquare(_x, _y);
	sq.clear(_z);
	Creature cr;
	Item it;
	for(thingsId = 0; thingsId < 11; thingsId++){
		if(p.getSize() < 2){
			cout<<"outOfData"<<endl;
			return false;
		}
		vAttr = p.peekUint16();
		if(vAttr >= 0xFF00){
			return true;
		}
		int getThing_ret = getThing(sq, _z, p);
		if(getThing_ret != 0){
			c->disconnect("getThing from getSquareMap");
			return false;
		}
	}
	return false;
}
