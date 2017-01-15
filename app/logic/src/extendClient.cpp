#include "extendClient.hpp"
#include "client.hpp"

ExtendClient::ExtendClient(Client* _c): c(_c){
	
}
/*
void ExtendClient::parseGMActions(NetworkPacket& p){

}
void ExtendClient::parseFYIMessage(NetworkPacket& p){

}
void ExtendClient::parseWaitingList(NetworkPacket& p){

}
void ExtendClient::parseDeath(NetworkPacket& p){

}
void ExtendClient::parseCanReportBugs(NetworkPacket& p){

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