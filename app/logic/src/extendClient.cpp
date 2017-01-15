#include "extendClient.hpp"
#include "client.hpp"

ExtendClient::ExtendClient(Client* _c): c(_c){
	
}
/*
void ExtendClient::parseSelfAppear(NetworkPacket& p){
	if(p.getSize()<7){
		c->disconnect("selfAppear too short");
		return;
	}
	c->id = p.getUint32();
	c->drawSpeed = p.getUint16();

	c->canReportBugs = p.getUint8()==1?true:false;
}
void ExtendClient::parseGMActions(NetworkPacket& p){

}
void ExtendClient::parseErrorMessage(NetworkPacket& p){
	if(p.getSize()<2 && p.getSize()<p.peakTStringSize()){
		disconnect("error message too short");
		return;
	}
	string error = p.getTString();
	cout<<"Error: "<<error<<endl;
}
void ExtendClient::parseFYIMessage(NetworkPacket& p){

}
void ExtendClient::parseWaitingList(NetworkPacket& p){

}
void ExtendClient::parsePing(NetworkPacket& p){
	conn->addPacket(PingPacket(xtea));
}
void ExtendClient::parseInit(NetworkPacket& p){
	if(p.getSize()<5){
		disconnect("parseInit too short");
		return;
	}
	for(int i=0;i<5;i++){
		verify_data[i] = p.getUint8();
	}
	cout<<"login to game server"<<endl;
	xtea.generateKeys();
	xtea_crypted = true;
	conn->addPacket(
		LoginPacket(login, password,
			version, os,
			dat_signature, spr_signature, pic_signature,
			verify_data, current_character.getName(),
			rsa, xtea)
		);
}
void ExtendClient::parseDeath(NetworkPacket& p){

}
void ExtendClient::parseCanReportBugs(NetworkPacket& p){

}
void ExtendClient::parseMapDescription(NetworkPacket& p){
	if(p.getSize() < 5) {
		disconnect("map description too short");
		return;
	}
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	gMap = Ground(mapViewX, mapViewY);
	cout<<"hero ("<<x<<","<<y<<","<<z<<")"<<endl;
	incoming_packet.dump();
	if(!getMap(p, x-8, y-6, z, 18, 14)){
		disconnect("failed to load map");
		return;
	}
}
bool ExtendClient::getMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t bz, int32_t w, int32_t h){
	int32_t currZ;
	cout<<"getMap"<<endl;
	if(bz > 7){
		int32_t endZ = bz + 2;
		if(endZ > mapLayers){
			endZ = mapLayers;
		}
		for(currZ = bz - 2; currZ < endZ; currZ++){
			if(!getFloorMap(p, bx, by, currZ, w, h)){
				return false;
			}
		}
	}else{
		for(currZ = 7; currZ > 0; currZ--){
			if(!getFloorMap(p, bx, by, currZ, w, h)){
				return false;
			}
		}
	}
	return true;
}
bool ExtendClient::getFloorMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t _z, int32_t w, int32_t h){
	int32_t cx, cy, skipTiles, vAttr;
	cout<<"getFloorMap "<<_z<<endl;
	skipTiles = 0;
	for(cx = 0; cx < w; cx++)
		for(cy = 0; cy < h; cy++){
			if(skipTiles == 0){
				if(p.getSize() < 2) {
					return false;
				}
				vAttr = p.peekUint16();
				if(vAttr > 0xEFFF){
					p.getUint16();
					skipTiles = vAttr & 0xFF;
				}else{
					if(!getSquareMap(p, bx + cx, by + cy, _z)){
						return false;
					}
					if(p.getSize() < 2) {
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
	cout<<"getSquareMap "<<_x<<","<<_y<<","<<_z<<endl;
	int32_t vAttr, thingsId;
	Square& sq = gMap.getSquare(_x, _y, _z);
	//TODO
	//sq.clear();
	for(thingsId = 0; thingsId < 10; thingsId++){
		if(p.getSize() < 2){
			return false;
		}
		vAttr = p.peekUint16();
		if(vAttr > 0xEFFF){
			return true;
		}
		Thing t = Thing(p);
		if(!t.good()){
			return false;
		}
		//TODO
		//sq.add(t);
	}
	return false;
}
void ExtendClient::parseMoveNorth(NetworkPacket& p){
	y--;
}
void ExtendClient::parseMoveEast(NetworkPacket& p){
	x++;
}
void ExtendClient::parseMoveSouth(NetworkPacket& p){
	y++;
}
void ExtendClient::parseMoveWest(NetworkPacket& p){
	x--;
}
void ExtendClient::parseUpdateTile(NetworkPacket& p){

}
void ExtendClient::parseTileAddThing(NetworkPacket& p){
	if(p.getSize()<9){
		disconnect("tileAddThing too short");
		return;
	}
	uint16_t x = p.getUint16();
	uint16_t y = p.getUint16();
	uint16_t z = p.getUint8();
	uint16_t stackId = p.getUint8();
	uint16_t itemId = p.getUint16();
	uint16_t attr = p.getUint8();
	(void)x;
	(void)y;
	(void)z;
	(void)stackId;
	(void)itemId;
	(void)attr;
	cout<<"add thing "<<itemId<<endl;
}
void ExtendClient::parseTileTransformThing(NetworkPacket& p){
	if(p.getSize()<9){
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t x = p.getUint16();
	uint16_t y = p.getUint16();
	uint16_t z = p.getUint8();
	uint16_t stackId = p.getUint8();
	uint16_t itemId = p.getUint16();
	uint16_t attr = p.getUint8();
	(void)x;
	(void)y;
	(void)z;
	(void)stackId;
	(void)itemId;
	(void)attr;
	cout<<"transform thing "<<itemId<<endl;
}
void ExtendClient::parseTileRemoveThing(NetworkPacket& p){
	if(p.getSize()<6) {
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t x = p.getUint16();
	uint16_t y = p.getUint16();
	uint16_t z = p.getUint8();
	uint16_t stackPos = p.getUint8();
	gMap.removeCreature(x, y, z, stackPos);
	cout<<"remove from "<<x<<","<<y<<","<<z<<" ("<<stackPos<<")"<<endl;
}
void ExtendClient::parseCreatureMove(NetworkPacket& p){
	if(p.getSize()<11) {
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t old_x = p.getUint16();
	uint16_t old_y = p.getUint16();
	uint16_t old_z = p.getUint8();
	uint16_t old_stackPos = p.getUint8();
	uint16_t new_x = p.getUint16();
	uint16_t new_y = p.getUint16();
	uint16_t new_z = p.getUint8();
	gMap.moveCreature(old_x, old_y, old_z, old_stackPos, new_x, new_y, new_z);
	cout<<"move from "<<old_x<<","<<old_y<<","<<old_z<<" ("<<old_stackPos<<")"
		<<" to "<<new_x<<","<<new_y<<","<<new_z<<endl;

}
void ExtendClient::parseOpenContainer(NetworkPacket& p){

}
void ExtendClient::parseCloseContainer(NetworkPacket& p){

}
void ExtendClient::parseContainerAddItem(NetworkPacket& p){

}
void ExtendClient::parseContainerUpdateItem(NetworkPacket& p){

}
void ExtendClient::parseContainerRemoveItem(NetworkPacket& p){

}
void ExtendClient::parseInventorySetSlot(NetworkPacket& p){
	if(p.getSize()<4){
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t slotId = p.getUint8();
	uint16_t itemId = p.getUint16();
	uint16_t attr = p.getUint8();
	cout<<"new item on slot"<<slotId<<" id "<<itemId<<" attr "<<attr<<endl;
}
void ExtendClient::parseInventoryResetSlot(NetworkPacket& p){
	if(p.getSize()<1){
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t slotId = p.getUint8();
	cout<<"reset slot"<<slotId<<endl;
}
void ExtendClient::parseSafeTradeRequestAck(NetworkPacket& p){

}
void ExtendClient::parseSafeTradeRequestNoAck(NetworkPacket& p){

}
void ExtendClient::parseSafeTradeClose(NetworkPacket& p){

}
void ExtendClient::parseWorldLight(NetworkPacket& p){
	if(p.getSize()>=2){
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t level = p.getUint8();
	uint16_t color = p.getUint8();
	gMap.parseLight(level, color);
	cout<<"world color "<<color<<" and level "<<level<<endl;
}
void ExtendClient::parseMagicEffect(NetworkPacket& p){

}
void ExtendClient::parseAnimatedText(NetworkPacket& p){

}
void ExtendClient::parseDistanceShot(NetworkPacket& p){

}
void ExtendClient::parseCreatureSquare(NetworkPacket& p){

}
void ExtendClient::parseCreatureHealth(NetworkPacket& p){
	if(p.getSize()<5){
		state = ExtendClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	uint16_t percent = p.getUint8();
	(void)id;
	(void)percent;
}
void ExtendClient::parseCreatureLight(NetworkPacket& p){
	if(p.getSize()<6){
		state = ExtendClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	uint16_t lvl = p.getUint8();
	uint16_t color = p.getUint8();
	(void)id;
	(void)lvl;
	(void)color;
}
void ExtendClient::parseCreatureOutfit(NetworkPacket& p){
	if(p.getSize()<4){
		state = ExtendClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	//HACK
	(void)id;
	//Outfit& tmpOut = gMap.getCreatureByID(id).getOutfit();
	Outfit tmpOut;
	if(!tmpOut.fromMsg(p)){
		state = ExtendClientState::NONE;
		return;
	}
}
void ExtendClient::parseCreatureSpeed(NetworkPacket& p){

}
void ExtendClient::parseCreatureSkulls(NetworkPacket& p){

}
void ExtendClient::parseCreatureShields(NetworkPacket& p){

}
void ExtendClient::parseCreaturePassable(NetworkPacket& p){

}
void ExtendClient::parseItemTextWindow(NetworkPacket& p){

}
void ExtendClient::parseHouseTextWindow(NetworkPacket& p){

}
void ExtendClient::parsePlayerStats(NetworkPacket& p){

}
void ExtendClient::parsePlayerSkills(NetworkPacket& p){

}
void ExtendClient::parsePlayerIcons(NetworkPacket& p){

}
void ExtendClient::parsePlayerCancelAttack(NetworkPacket& p){

}
void ExtendClient::parseCreatureSpeak(NetworkPacket& p){
	if(p.getSize()<10){
		state = ExtendClientState::NONE;
		return;
	}
	uint32_t unkSpeak = p.getUint32();
	if(p.getSize()<2 && p.getSize()<(p.peakTStringSize()+2)){
		state = ExtendClientState::NONE;
		return;
	}
	string name = p.getTString();
	uint16_t level = p.getUint16();
	uint16_t type = p.getUint16();
	cout<<"speak "<<unkSpeak<<" "<<name<<" "<<level<<" "<<type<<endl;
}
void ExtendClient::parseChannelList(NetworkPacket& p){

}
void ExtendClient::parseOpenChannel(NetworkPacket& p){

}
void ExtendClient::parseOpenPrivatePlayerChat(NetworkPacket& p){

}
void ExtendClient::parseOpenRuleViolation(NetworkPacket& p){

}
void ExtendClient::parseRuleViolationAF(NetworkPacket& p){

}
void ExtendClient::parseRuleViolationB0(NetworkPacket& p){

}
void ExtendClient::parseRuleViolationB1(NetworkPacket& p){

}
void ExtendClient::parseCreatePrivateChannel(NetworkPacket& p){

}
void ExtendClient::parseClosePrivateChannel(NetworkPacket& p){

}
void ExtendClient::parseTextMessage(NetworkPacket& p){
	if(p.getSize()<1){
		state = ExtendClientState::NONE;
		return;
	}
	uint16_t type = p.getUint8();
	if(p.getSize()<2 && p.getSize()<(p.peakTStringSize()+2)){
		state = ExtendClientState::NONE;
		return;
	}
	std::string msg = p.getTString();
	cout<<"type: "<<type<<": "<<msg<<endl;
}
void ExtendClient::parsePlayerCancelWalk(NetworkPacket& p){

}
void ExtendClient::parseFloorChangeUp(NetworkPacket& p){

}
void ExtendClient::parseFloorChangeDown(NetworkPacket& p){

}
void ExtendClient::parseOutfitWindow(NetworkPacket& p){

}
void ExtendClient::parseVipState(NetworkPacket& p){

}
void ExtendClient::parseVipLogin(NetworkPacket& p){

}
void ExtendClient::parseVipLogout(NetworkPacket& p){

}
void ExtendClient::parseQuestList(NetworkPacket& p){

}
void ExtendClient::parseQuestPartList(NetworkPacket& p){

}
void ExtendClient::parseOpenShopWindow(NetworkPacket& p){

}
void ExtendClient::parsePlayerCash(NetworkPacket& p){

}
void ExtendClient::parseCloseShopWindow(NetworkPacket& p){

}
void ExtendClient::parseShowTutorial(NetworkPacket& p){

}
void ExtendClient::parseAddMapMarker(NetworkPacket& p){

}
*/