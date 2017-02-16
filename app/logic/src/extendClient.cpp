#include "extendClient.hpp"
#include "client.hpp"

ExtendClient::ExtendClient(Client* _c): c(_c){
	cbs_names[0xDD] = "AddMapMarker";
	//cbs_funcs[0xDD] = &ExtendClient::AddMapMarker;
	cbs_names[0x84] = "AnimatedText";
	//cbs_funcs[0x84] = &ExtendClient::AnimatedText;
	cbs_names[0x32] = "CanReportBugs";
	//cbs_funcs[0x32] = &ExtendClient::CanReportBugs;
	cbs_names[0xAB] = "ChannelList";
	//cbs_funcs[0xAB] = &ExtendClient::ChannelList;
	cbs_names[0x6F] = "CloseContainer";
	//cbs_funcs[0x6F] = &ExtendClient::CloseContainer;
	cbs_names[0xB3] = "ClosePrivateChannel";
	//cbs_funcs[0xB3] = &ExtendClient::ClosePrivateChannel;
	cbs_names[0x7C] = "CloseShopWindow";
	//cbs_funcs[0x7C] = &ExtendClient::CloseShopWindow;
	cbs_names[0x70] = "ContainerAddItem";
	//cbs_funcs[0x70] = &ExtendClient::ContainerAddItem;
	cbs_names[0x72] = "ContainerRemoveItem";
	//cbs_funcs[0x72] = &ExtendClient::ContainerRemoveItem;
	cbs_names[0x71] = "ContainerUpdateItem";
	//cbs_funcs[0x71] = &ExtendClient::ContainerUpdateItem;
	cbs_names[0xB2] = "CreatePrivateChannel";
	//cbs_funcs[0xB2] = &ExtendClient::CreatePrivateChannel;
	cbs_names[0x8C] = "CreatureHealth";
	cbs_funcs[0x8C] = &ExtendClient::CreatureHealth;
	cbs_names[0x8D] = "CreatureLight";
	cbs_funcs[0x8D] = &ExtendClient::CreatureLight;
	cbs_names[0x6D] = "CreatureMove";
	cbs_funcs[0x6D] = &ExtendClient::CreatureMove;
	cbs_names[0x8E] = "CreatureOutfit";
	//cbs_funcs[0x8E] = &ExtendClient::CreatureOutfit;
	cbs_names[0x92] = "CreaturePassable";
	cbs_funcs[0x92] = &ExtendClient::CreaturePassable;
	cbs_names[0x91] = "CreatureShields";
	//cbs_funcs[0x91] = &ExtendClient::CreatureShields;
	cbs_names[0x90] = "CreatureSkulls";
	//cbs_funcs[0x90] = &ExtendClient::CreatureSkulls;
	cbs_names[0xAA] = "CreatureSpeak";
	cbs_funcs[0xAA] = &ExtendClient::CreatureSpeak;
	cbs_names[0x8F] = "CreatureSpeed";
	//cbs_funcs[0x8F] = &ExtendClient::CreatureSpeed;
	cbs_names[0x86] = "CreatureSquare";
	//cbs_funcs[0x86] = &ExtendClient::CreatureSquare;
	cbs_names[0x28] = "Death";
	//cbs_funcs[0x28] = &ExtendClient::Death;
	cbs_names[0x85] = "DistanceShot";
	//cbs_funcs[0x85] = &ExtendClient::DistanceShot;
	cbs_names[0x14] = "ErrorMessage";
	cbs_funcs[0x14] = &ExtendClient::ErrorMessage;
	cbs_names[0x15] = "FYIMessage";
	//cbs_funcs[0x15] = &ExtendClient::FYIMessage;
	cbs_names[0xBF] = "FloorChangeDown";
	//cbs_funcs[0xBF] = &ExtendClient::FloorChangeDown;
	cbs_names[0xBE] = "FloorChangeUp";
	//cbs_funcs[0xBE] = &ExtendClient::FloorChangeUp;
	cbs_names[0x0B] = "GMActions";
	//cbs_funcs[0x0B] = &ExtendClient::GMActions;
	cbs_names[0x97] = "HouseTextWindow";
	//cbs_funcs[0x97] = &ExtendClient::HouseTextWindow;
	cbs_names[0x1F] = "Init";
	cbs_funcs[0x1F] = &ExtendClient::Init;
	cbs_names[0x79] = "InventoryResetSlot";
	cbs_funcs[0x79] = &ExtendClient::InventoryResetSlot;
	cbs_names[0x78] = "InventorySetSlot";
	cbs_funcs[0x78] = &ExtendClient::InventorySetSlot;
	cbs_names[0x96] = "ItemTextWindow";
	//cbs_funcs[0x96] = &ExtendClient::ItemTextWindow;
	cbs_names[0x83] = "MagicEffect";
	cbs_funcs[0x83] = &ExtendClient::MagicEffect;
	cbs_names[0x64] = "MapDescription";
	cbs_funcs[0x64] = &ExtendClient::MapDescription;
	cbs_names[0x66] = "MoveEast";
	cbs_funcs[0x66] = &ExtendClient::MoveEast;
	cbs_names[0x65] = "MoveNorth";
	cbs_funcs[0x65] = &ExtendClient::MoveNorth;
	cbs_names[0x67] = "MoveSouth";
	cbs_funcs[0x67] = &ExtendClient::MoveSouth;
	cbs_names[0x68] = "MoveWest";
	cbs_funcs[0x68] = &ExtendClient::MoveWest;
	cbs_names[0xAC] = "OpenChannel";
	//cbs_funcs[0xAC] = &ExtendClient::OpenChannel;
	cbs_names[0x6E] = "OpenContainer";
	//cbs_funcs[0x6E] = &ExtendClient::OpenContainer;
	cbs_names[0xAD] = "OpenPrivatePlayerChat";
	//cbs_funcs[0xAD] = &ExtendClient::OpenPrivatePlayerChat;
	cbs_names[0xAE] = "OpenRuleViolation";
	//cbs_funcs[0xAE] = &ExtendClient::OpenRuleViolation;
	cbs_names[0x7A] = "OpenShopWindow";
	//cbs_funcs[0x7A] = &ExtendClient::OpenShopWindow;
	cbs_names[0xC8] = "OutfitWindow";
	//cbs_funcs[0xC8] = &ExtendClient::OutfitWindow;
	cbs_names[0x1E] = "Ping";
	cbs_funcs[0x1E] = &ExtendClient::Ping;
	cbs_names[0xA3] = "PlayerCancelAttack";
	//cbs_funcs[0xA3] = &ExtendClient::PlayerCancelAttack;
	cbs_names[0xB5] = "PlayerCancelWalk";
	//cbs_funcs[0xB5] = &ExtendClient::PlayerCancelWalk;
	cbs_names[0x7B] = "PlayerCash";
	//cbs_funcs[0x7B] = &ExtendClient::PlayerCash;
	cbs_names[0xA2] = "PlayerIcons";
	cbs_funcs[0xA2] = &ExtendClient::PlayerIcons;
	cbs_names[0xA1] = "PlayerSkills";
	cbs_funcs[0xA1] = &ExtendClient::PlayerSkills;
	cbs_names[0xA0] = "PlayerStats";
	cbs_funcs[0xA0] = &ExtendClient::PlayerStats;
	cbs_names[0xF0] = "QuestList";
	//cbs_funcs[0xF0] = &ExtendClient::QuestList;
	cbs_names[0xF1] = "QuestPartList";
	//cbs_funcs[0xF1] = &ExtendClient::QuestPartList;
	cbs_names[0xAF] = "RuleViolationAF";
	//cbs_funcs[0xAF] = &ExtendClient::RuleViolationAF;
	cbs_names[0xB0] = "RuleViolationB0";
	//cbs_funcs[0xB0] = &ExtendClient::RuleViolationB0;
	cbs_names[0xB1] = "RuleViolationB1";
	//cbs_funcs[0xB1] = &ExtendClient::RuleViolationB1;
	cbs_names[0x7F] = "SafeTradeClose";
	//cbs_funcs[0x7F] = &ExtendClient::SafeTradeClose;
	cbs_names[0x7D] = "SafeTradeRequestAck";
	//cbs_funcs[0x7D] = &ExtendClient::SafeTradeRequestAck;
	cbs_names[0x7E] = "SafeTradeRequestNoAck";
	//cbs_funcs[0x7E] = &ExtendClient::SafeTradeRequestNoAck;
	cbs_names[0x0A] = "SelfAppear";
	cbs_funcs[0x0A] = &ExtendClient::SelfAppear;
	cbs_names[0xDC] = "ShowTutorial";
	//cbs_funcs[0xDC] = &ExtendClient::ShowTutorial;
	cbs_names[0xB4] = "TextMessage";
	cbs_funcs[0xB4] = &ExtendClient::TextMessage;
	cbs_names[0x6A] = "TileAddThing";
	cbs_funcs[0x6A] = &ExtendClient::TileAddThing;
	cbs_names[0x6C] = "TileRemoveThing";
	cbs_funcs[0x6C] = &ExtendClient::TileRemoveThing;
	cbs_names[0x6B] = "TileUpdateItem";
	cbs_funcs[0x6B] = &ExtendClient::TileUpdateItem;
	cbs_names[0x69] = "UpdateTile";
	//cbs_funcs[0x69] = &ExtendClient::UpdateTile;
	cbs_names[0xD3] = "VipLogin";
	//cbs_funcs[0xD3] = &ExtendClient::VipLogin;
	cbs_names[0xD4] = "VipLogout";
	//cbs_funcs[0xD4] = &ExtendClient::VipLogout;
	cbs_names[0xD2] = "VipState";
	cbs_funcs[0xD2] = &ExtendClient::VipState;
	cbs_names[0x16] = "WaitingList";
	//cbs_funcs[0x16] = &ExtendClient::WaitingList;
	cbs_names[0x82] = "WorldLight";
	cbs_funcs[0x82] = &ExtendClient::WorldLight;
}
<<<<<<< HEAD
#ifdef DEBUG_CB
bool ExtendClient::getCallback(
	void(ExtendClient::*&func_addr)(NetworkPacket& p), 
	std::string& func_name,
	uint16_t type
){
	std::map<uint16_t, std::string>::iterator name;
	std::map<uint16_t, void(ExtendClient::*)(class NetworkPacket& p)>::iterator func;
	name = cbs_names.find(type);
	func = cbs_funcs.find(type);
	if(name != cbs_names.end()){
		func_name = name->second;
	}
	if(func == cbs_funcs.end()){
		return false;
	}else{
		func_addr = func->second;
		return true;
	}
=======
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

>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}
#else
bool ExtendClient::getCallback(
	void(ExtendClient::*&func_addr)(NetworkPacket& p), 
	uint16_t type
){
	std::map<uint16_t, void(ExtendClient::*)(class NetworkPacket& p)>::iterator func;
	func = cbs_funcs.find(type);
	if(func == cbs_funcs.end()){
		return false;
	}else{
		func_addr = func->second;
		return true;
	}
}
#endif