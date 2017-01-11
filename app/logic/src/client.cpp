#include "client.hpp"
#include <iostream>
#include "packets/LoginPacket.hpp"
#include "packets/PingPacket.hpp"
#include "packets/MovePacket.hpp"
#include "thing.hpp"

#include <sstream>

using namespace std;
using namespace std::chrono;

Character::Character():
port(0), valid(false)
{
	oip[0]=0;
	oip[1]=0;
	oip[2]=0;
	oip[3]=0;
}
Character::Character(std::string _nick, std::string _world, uint32_t _ip, uint16_t _port):
nick(_nick), world(_world), port(_port), valid(true)
{
	oip[0]=(_ip    )&0xff;
	oip[1]=(_ip>> 8)&0xff;
	oip[2]=(_ip>>16)&0xff;
	oip[3]=(_ip>>24)&0xff;
}
bool Character::isValid(){
	return valid;
}
string Character::getAddress(){
	stringstream str;
	str<<oip[0]<<"."<<oip[1]<<"."<<oip[2]<<"."<<oip[3]<<":"<<port;
	return str.str();
}
std::string Character::getName(){
	return nick;
}

Client::Client(string ip, uint16_t _version, uint16_t _os, string l, string p):
	rsa(rsa_m_n, rsa_e_n),
	version(_version), os(_os),
	login(l), password(p)
{
	lastAntyIdle = chrono::system_clock::now();
	AntyIdle_duration = chrono::seconds(1);
	conn = 0;
	afterRecvFunc = [](){};
	newConnection(ip);
	state = ClientState::LOGIN;
	xtea_crypted = true;
	conn->addPacket(LoginPacket(login, password, version, os, dat_signature, spr_signature, pic_signature, rsa, xtea));
}
Client::~Client(){
	closeConnection();
}
void Client::newConnection(std::string ip){
	if(conn != 0){
		closeConnection();
	}
	conn = new NetworkManager(ip);
}
void Client::closeConnection(){
	delete conn;
	conn = 0;
}
void Client::loginListener(std::function<void(int, std::string)> cb){
	changeStateFunc = cb;
}
void Client::afterRecv(std::function<void(void)> cb){
	afterRecvFunc = cb;
}
void Client::listChars(std::function<void(std::string, size_t)> cb){
	size_t s = characters.size();
	for(size_t i=0;i<s;i++){
		cb(characters[i].getName(), i);
	}
}
bool Client::setChar(size_t id){
	if(id == -1){
		if(state == ClientState::GAME){
			closeConnection();
		}
		current_character = Character();
		state = ClientState::WAIT_TO_ENTER;
	}else if(id<characters.size()){
		current_character = characters[id];
		if (current_character.isValid()){
			newConnection(current_character.getAddress());
			xtea_crypted = false;
			state = ClientState::GAME;
			return true;
		} else {
			state = ClientState::NONE;
			return false;
		}
	}
	return false;
}
void Client::recv(){
	if(xtea_crypted){
		incoming_packet.xteaDecrypt(xtea);
	}
	uint16_t len = incoming_packet.getUint16();
	uint16_t real_len = incoming_packet.getSize();
	if(real_len < len){
		cout<<"wrong size after XTea decrypt, expected "<<len<<" but has "<<real_len<<endl;
		return;
	}
	incoming_packet.resize(len);
	uint16_t packetType;
	while(true){
		switch(state){
			case ClientState::NONE:{
				closeConnection();
				changeStateFunc(3, "");
			}break;
			case ClientState::LOGIN:{
				state = ClientState::NONE;
				closeConnection();
				do{
					packetType = incoming_packet.getUint8();
					switch(packetType){
						case 0x0A:{ //Error message
							std::string errormsg = incoming_packet.getTString();
							changeStateFunc(2, errormsg);
							state = ClientState::NONE;
						}break;
						case 0x0B:{ //For your information
							std::string infomsg = incoming_packet.getTString();
							cout<<"Info: "<<infomsg<<endl;
						}break;
						case 0x14:{ //MOTD
							std::string motd = incoming_packet.getTString();
							cout<<"Motd "<<motd<<endl;
						}break;
						case 0x1E: //Patching exe/dat/spr messages
						case 0x1F:
						case 0x20:
							changeStateFunc(2, "need to patch");
							state = ClientState::NONE;
						break;
						case 0x28: //Select other login server
							changeStateFunc(2, "Select other login server");
							state = ClientState::NONE;
						break;
						case 0x64:{ //character list
							uint16_t nchars = incoming_packet.getUint8();
							for(uint32_t i = 0; i < nchars; ++i){
								std::string charName = incoming_packet.getTString();
								std::string world = incoming_packet.getTString();
								uint32_t ip = incoming_packet.getUint32();
								uint16_t port = incoming_packet.getUint16();
								characters.push_back(Character(charName, world, ip, port));
							}
							premiumDays = incoming_packet.getUint16();
							state = ClientState::WAIT_TO_ENTER;
						}break;
					}
				}while(incoming_packet.getSize()>=1);
				if(state != ClientState::NONE){
					continue;
				}
			}break;
			case ClientState::WAIT_TO_ENTER:
				changeStateFunc(4, "");
				cout<<"wait"<<endl;
			break;
			case ClientState::ENTER_GAME:{
				if (!current_character.isValid() && characters.size()>0){
					newConnection(current_character.getAddress());
					xtea_crypted = false;
					state = ClientState::GAME;
					cout<<"enter to game"<<endl;
				}
				else {
					cout<<"no valid"<<endl;
					state = ClientState::NONE;
				}
			}break;
			case ClientState::GAME:{
				if(!current_character.isValid()){
					state = ClientState::NONE;
					closeConnection();
				}
				packetType = incoming_packet.getUint8();
				cout<<"packet "<<packetType<<endl;
				switch(packetType){
					case 0x0A:
						parseSelfAppear(incoming_packet);
					break;
					/*case 0x0B:
						parseGMActions(incoming_packet);
					break;
					*/
					case 0x14:
						parseErrorMessage(incoming_packet);
					break;
					/*case 0x15:
						parseFYIMessage(incoming_packet);
					break;
					case 0x16:
						parseWaitingList(incoming_packet);
					break;
					*/
					case 0x1E:
						parsePing(incoming_packet);
					break;
					case 0x1F:
						parseInit(incoming_packet);
					break;
					/*case 0x28:
						parseDeath(incoming_packet);
					break;
					case 0x32:
						parseCanReportBugs(incoming_packet);
					break;
					*/
					case 0x64:
						parseMapDescription(incoming_packet);
					break;
					case 0x65:
						parseMoveNorth(incoming_packet);
					break;
					case 0x66:
						parseMoveEast(incoming_packet);
					break;
					case 0x67:
						parseMoveSouth(incoming_packet);
					break;
					case 0x68:
						parseMoveWest(incoming_packet);
					break;
					/*case 0x69:
						parseUpdateTile(incoming_packet);
					break;*/
					case 0x6A:
						parseTileAddThing(incoming_packet);
					break;
					/*case 0x6B:
						parseTileTransformThing(incoming_packet);
					break;
					case 0x6C:
						parseTileRemoveThing(incoming_packet);
					break;*/
					case 0x6D:
						parseCreatureMove(incoming_packet);
					break;
					/*case 0x6E:
						parseOpenContainer(incoming_packet);
					break;
					case 0x6F:
						parseCloseContainer(incoming_packet);
					break;
					case 0x70:
						parseContainerAddItem(incoming_packet);
					break;
					case 0x71:
						parseContainerUpdateItem(incoming_packet);
					break;
					case 0x72:
						parseContainerRemoveItem(incoming_packet);
					break;
					*/
					case 0x78:
						parseInventorySetSlot(incoming_packet);
					break;
					case 0x79:
						parseInventoryResetSlot(incoming_packet);
					break;
					/*case 0x7D:
						parseSafeTradeRequestAck(incoming_packet);
					break;
					case 0x7E:
						parseSafeTradeRequestNoAck(incoming_packet);
					break;
					case 0x7F:
						parseSafeTradeClose(incoming_packet);
					break;
					*/
					case 0x82:
						parseWorldLight(incoming_packet);
					break;
					case 0x83:
						parseMagicEffect(incoming_packet);
					break;
					/*case 0x84:
						parseAnimatedText(incoming_packet);
					break;
					case 0x85:
						parseDistanceShot(incoming_packet);
					break;
					case 0x86:
						parseCreatureSquare(incoming_packet);
					break;
					*/
					case 0x8C:
						parseCreatureHealth(incoming_packet);
					break;
					case 0x8D:
						parseCreatureLight(incoming_packet);
					break;
					/*case 0x8E:
						parseCreatureOutfit(incoming_packet);
					break;
					case 0x8F:
						parseCreatureSpeed(incoming_packet);
					break;
					case 0x90:
						parseCreatureSkulls(incoming_packet);
					break;
					case 0x91:
						parseCreatureShields(incoming_packet);
					break;
					case 0x92:
						parseCreaturePassable(incoming_packet);
					break;
					case 0x96:
						parseItemTextWindow(incoming_packet);
					break;
					case 0x97:
						parseHouseTextWindow(incoming_packet);
					break;
					case 0xA0:
						parsePlayerStats(incoming_packet);
					break;
					case 0xA1:
						parsePlayerSkills(incoming_packet);
					break;
					case 0xA2:
						parsePlayerIcons(incoming_packet);
					break;
					case 0xA3:
						parsePlayerCancelAttack(incoming_packet);
					break;
					*/
					case 0xAA:
						parseCreatureSpeak(incoming_packet);
					break;
					/*case 0xAB:
						parseChannelList(incoming_packet);
					case 0xAC:
						parseOpenChannel(incoming_packet);
					break;
					case 0xAD:
						parseOpenPrivatePlayerChat(incoming_packet);
					break;
					case 0xAE:
						parseOpenRuleViolation(incoming_packet);
					break;
					case 0xAF:
						parseRuleViolationAF(incoming_packet);
					break;
					case 0xB0:
						parseRuleViolationB0(incoming_packet);
					break;
					case 0xB1:
						parseRuleViolationB1(incoming_packet);
					break;
					case 0xB2:
						parseCreatePrivateChannel(incoming_packet);
					break;
					case 0xB3:
						parseClosePrivateChannel(incoming_packet);
					break;
					*/
					case 0xB4:
						parseTextMessage(incoming_packet);
					break;
					/*case 0xB5:
						parsePlayerCancelWalk(incoming_packet);
					break;
					case 0xBE:
						parseFloorChangeUp(incoming_packet);
					break;
					case 0xBF:
						parseFloorChangeDown(incoming_packet);
					break;
					case 0xC8:
						parseOutfitWindow(incoming_packet);
					break;
					case 0xD2:
						parseVipState(incoming_packet);
					break;
					case 0xD3:
						parseVipLogin(incoming_packet);
					break;
					case 0xD4:
						parseVipLogout(incoming_packet);
					break;
					case 0xF0:
						parseQuestList(incoming_packet);
					break;
					case 0xF1:
						parseQuestPartList(incoming_packet);
					break;
					case 0x7A:
						parseOpenShopWindow(incoming_packet);
					break;
					case 0x7B:
						parsePlayerCash(incoming_packet);
					break;
					case 0x7C:
						parseCloseShopWindow(incoming_packet);
					break;
					case 0xDC:
						parseShowTutorial(incoming_packet);
					break;
					case 0xDD:
						parseAddMapMarker(incoming_packet);
					break;
					*/
					default:
						cout<<"unknown packet type "<<packetType<<endl;
						incoming_packet.dump();
						return;
				}
				if(incoming_packet.getSize()>0){
					continue;
				}
			}break;
		}
		break;
	}
}

void Client::idle(){
	system_clock::time_point now = chrono::system_clock::now();
	seconds elapsed = chrono::duration_cast<chrono::seconds>(now - lastAntyIdle);
	//chrono::seconds antyafk_elapse_sec = chrono::duration_cast<chrono::seconds>  = now - lastAntyIdle;
	if(elapsed > AntyIdle_duration){
		//move(ClientDirectory::STOP);
		lastAntyIdle = now;
	}
}

int Client::tick(){
	if(conn == 0){
		return 1;
	}
	int st = conn->tick();
	if(st == 1){
		changeStateFunc(5, "");
		return 0;
	}
	else if(st == 2){
		if(conn->getPacket(incoming_packet)){
			recv();
			afterRecvFunc();
		}
	}else{
		idle();
	}
	return 1;
}

void Client::parseSelfAppear(NetworkPacket& p){
	if(p.getSize()<7){
		state = ClientState::NONE;
		return;
	}
	id = p.getUint32();
	drawSpeed = p.getUint16();

	canReportBugs = p.getUint8()==1?true:false;
}
void Client::parseGMActions(NetworkPacket& p){

}
void Client::parseErrorMessage(NetworkPacket& p){
	if(p.getSize()<2 && p.getSize()<p.peakTStringSize()){
		state = ClientState::NONE;
		return;
	}
	string error = p.getTString();
	cout<<"Error: "<<error<<endl;
}
void Client::parseFYIMessage(NetworkPacket& p){

}
void Client::parseWaitingList(NetworkPacket& p){

}
void Client::parsePing(NetworkPacket& p){
	conn->addPacket(PingPacket(xtea));
}
void Client::parseInit(NetworkPacket& p){
	if(p.getSize()<5){
		state = ClientState::NONE;
		return;
	}
	for(int i=0;i<5;i++){
		verify_data[i] = p.getUint8();
	}
	cout<<"login to game server"<<endl;
	gMap = Ground(mapViewX, mapViewY);
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
void Client::parseDeath(NetworkPacket& p){

}
void Client::parseCanReportBugs(NetworkPacket& p){

}
void Client::parseMapDescription(NetworkPacket& p){
	if(p.getSize() < 5) {
		state = ClientState::NONE;
		return;
	}
	x = p.getUint16();
	y = p.getUint16();
	z = p.getUint8();
	cout<<"hero ("<<x<<","<<y<<","<<z<<")"<<endl;
	incoming_packet.dump();
	if(!getMap(p, x-8, y-6, z, 18, 14)){
		state = ClientState::NONE;
		return;
	}
}
bool Client::getMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t bz, int32_t w, int32_t h){
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
bool Client::getFloorMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t _z, int32_t w, int32_t h){
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
bool Client::getSquareMap(NetworkPacket& p, int32_t _x, int32_t _y, int32_t _z){
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
void Client::parseMoveNorth(NetworkPacket& p){
	y--;
}
void Client::parseMoveEast(NetworkPacket& p){
	x++;
}
void Client::parseMoveSouth(NetworkPacket& p){
	y++;
}
void Client::parseMoveWest(NetworkPacket& p){
	x--;
}
void Client::parseUpdateTile(NetworkPacket& p){

}
void Client::parseTileAddThing(NetworkPacket& p){
	if(p.getSize()<9){
		state = ClientState::NONE;
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
void Client::parseTileTransformThing(NetworkPacket& p){
	if(p.getSize()<9){
		state = ClientState::NONE;
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
void Client::parseTileRemoveThing(NetworkPacket& p){
	if(p.getSize()<6) {
		state = ClientState::NONE;
		return;
	}
	uint16_t x = p.getUint16();
	uint16_t y = p.getUint16();
	uint16_t z = p.getUint8();
	uint16_t stackPos = p.getUint8();
	gMap.removeCreature(x, y, z, stackPos);
	cout<<"remove from "<<x<<","<<y<<","<<z<<" ("<<stackPos<<")"<<endl;
}
void Client::parseCreatureMove(NetworkPacket& p){
	if(p.getSize()<11) {
		state = ClientState::NONE;
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
void Client::parseOpenContainer(NetworkPacket& p){

}
void Client::parseCloseContainer(NetworkPacket& p){

}
void Client::parseContainerAddItem(NetworkPacket& p){

}
void Client::parseContainerUpdateItem(NetworkPacket& p){

}
void Client::parseContainerRemoveItem(NetworkPacket& p){

}
void Client::parseInventorySetSlot(NetworkPacket& p){
	if(p.getSize()<4){
		state = ClientState::NONE;
		return;
	}
	uint16_t slotId = p.getUint8();
	uint16_t itemId = p.getUint16();
	uint16_t attr = p.getUint8();
	cout<<"new item on slot"<<slotId<<" id "<<itemId<<" attr "<<attr<<endl;
}
void Client::parseInventoryResetSlot(NetworkPacket& p){
	if(p.getSize()<1){
		state = ClientState::NONE;
		return;
	}
	uint16_t slotId = p.getUint8();
	cout<<"reset slot"<<slotId<<endl;
}
void Client::parseSafeTradeRequestAck(NetworkPacket& p){

}
void Client::parseSafeTradeRequestNoAck(NetworkPacket& p){

}
void Client::parseSafeTradeClose(NetworkPacket& p){

}
void Client::parseWorldLight(NetworkPacket& p){
	if(p.getSize()>=2){
		state = ClientState::NONE;
		return;
	}
	uint16_t level = p.getUint8();
	uint16_t color = p.getUint8();
	gMap.parseLight(level, color);
	cout<<"world color "<<color<<" and level "<<level<<endl;
}
void Client::parseMagicEffect(NetworkPacket& p){

}
void Client::parseAnimatedText(NetworkPacket& p){

}
void Client::parseDistanceShot(NetworkPacket& p){

}
void Client::parseCreatureSquare(NetworkPacket& p){

}
void Client::parseCreatureHealth(NetworkPacket& p){
	if(p.getSize()<5){
		state = ClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	uint16_t percent = p.getUint8();
	(void)id;
	(void)percent;
}
void Client::parseCreatureLight(NetworkPacket& p){
	if(p.getSize()<6){
		state = ClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	uint16_t lvl = p.getUint8();
	uint16_t color = p.getUint8();
	(void)id;
	(void)lvl;
	(void)color;
}
void Client::parseCreatureOutfit(NetworkPacket& p){
	if(p.getSize()<4){
		state = ClientState::NONE;
		return;
	}
	uint32_t id = p.getUint32();
	//HACK
	(void)id;
	//Outfit& tmpOut = gMap.getCreatureByID(id).getOutfit();
	Outfit tmpOut;
	if(!tmpOut.fromMsg(p)){
		state = ClientState::NONE;
		return;
	}
}
void Client::parseCreatureSpeed(NetworkPacket& p){

}
void Client::parseCreatureSkulls(NetworkPacket& p){

}
void Client::parseCreatureShields(NetworkPacket& p){

}
void Client::parseCreaturePassable(NetworkPacket& p){

}
void Client::parseItemTextWindow(NetworkPacket& p){

}
void Client::parseHouseTextWindow(NetworkPacket& p){

}
void Client::parsePlayerStats(NetworkPacket& p){

}
void Client::parsePlayerSkills(NetworkPacket& p){

}
void Client::parsePlayerIcons(NetworkPacket& p){

}
void Client::parsePlayerCancelAttack(NetworkPacket& p){

}
void Client::parseCreatureSpeak(NetworkPacket& p){
	if(p.getSize()<10){
		state = ClientState::NONE;
		return;
	}
	uint32_t unkSpeak = p.getUint32();
	if(p.getSize()<2 && p.getSize()<(p.peakTStringSize()+2)){
		state = ClientState::NONE;
		return;
	}
	string name = p.getTString();
	uint16_t level = p.getUint16();
	uint16_t type = p.getUint16();
	cout<<"speak "<<unkSpeak<<" "<<name<<" "<<level<<" "<<type<<endl;
}
void Client::parseChannelList(NetworkPacket& p){

}
void Client::parseOpenChannel(NetworkPacket& p){

}
void Client::parseOpenPrivatePlayerChat(NetworkPacket& p){

}
void Client::parseOpenRuleViolation(NetworkPacket& p){

}
void Client::parseRuleViolationAF(NetworkPacket& p){

}
void Client::parseRuleViolationB0(NetworkPacket& p){

}
void Client::parseRuleViolationB1(NetworkPacket& p){

}
void Client::parseCreatePrivateChannel(NetworkPacket& p){

}
void Client::parseClosePrivateChannel(NetworkPacket& p){

}
void Client::parseTextMessage(NetworkPacket& p){
	if(p.getSize()<1){
		state = ClientState::NONE;
		return;
	}
	uint16_t type = p.getUint8();
	if(p.getSize()<2 && p.getSize()<(p.peakTStringSize()+2)){
		state = ClientState::NONE;
		return;
	}
	std::string msg = p.getTString();
	cout<<"type: "<<type<<": "<<msg<<endl;
}
void Client::parsePlayerCancelWalk(NetworkPacket& p){

}
void Client::parseFloorChangeUp(NetworkPacket& p){

}
void Client::parseFloorChangeDown(NetworkPacket& p){

}
void Client::parseOutfitWindow(NetworkPacket& p){

}
void Client::parseVipState(NetworkPacket& p){

}
void Client::parseVipLogin(NetworkPacket& p){

}
void Client::parseVipLogout(NetworkPacket& p){

}
void Client::parseQuestList(NetworkPacket& p){

}
void Client::parseQuestPartList(NetworkPacket& p){

}
void Client::parseOpenShopWindow(NetworkPacket& p){

}
void Client::parsePlayerCash(NetworkPacket& p){

}
void Client::parseCloseShopWindow(NetworkPacket& p){

}
void Client::parseShowTutorial(NetworkPacket& p){

}
void Client::parseAddMapMarker(NetworkPacket& p){

}

void Client::move(ClientDirectory dir){
	conn->addPacket(MovePacket(dir, xtea));
}
