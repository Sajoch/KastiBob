#include "client.hpp"
#include <iostream>
#include "packets/LoginPacket.hpp"
#include <sstream>

using namespace std;

enum class ClientState { 
	NONE, LOGIN, ENTER_GAME, GAME, INIT_GAME,
};
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
Client::Client(string ip, uint16_t _version, uint16_t _os, string l, string p):
	rsa(rsa_m_n, rsa_e_n),
	version(_version), os(_os),
	login(l), password(p)
{
	conn = 0;
	newConnection(ip);
	state = ClientState::LOGIN;
	xtea_crypted = true;
	conn->addPacket(LoginPacket(login, password, version, os, dat_signature, spr_signature, pic_signature, rsa, xtea));
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
void Client::idle(){
	if(xtea_crypted)
		incoming_packet.xteaDecrypt(xtea);
	uint16_t len = incoming_packet.getUint16();
	uint16_t real_len = incoming_packet.getSize();
	if(real_len != len && (real_len - len) > 3){		
		cout<<"wrong size after XTea decrypt, expected "<<len<<" but has "<<real_len<<endl;
		return;
	}
	uint16_t packetType;
	while(true){
		switch(state){
			case ClientState::NONE:{
				cout<<"none"<<endl;
				closeConnection();
			}break;
			case ClientState::LOGIN:{
				state = ClientState::NONE;
				closeConnection();
				do{
					packetType = incoming_packet.getUint8();
					switch(packetType){
						case 0x0A:{ //Error message
							std::string errormsg = incoming_packet.getTString();
							cout<<"Error: "<<errormsg<<endl;
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
							cout<<"need to patch"<<endl;
						break;
						case 0x28: //Select other login server
							cout<<"Select other login server"<<endl;
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
							state = ClientState::ENTER_GAME;
						}break;
					}
				}while(incoming_packet.getSize()>=1);
				
				if(state != ClientState::NONE){
					continue;
				}
			}break;
			case ClientState::ENTER_GAME:{
				if (!currenct_character.isValid() && characters.size()>0){
					//TODO auto select character
					currenct_character = characters[0];
					newConnection(currenct_character.getAddress());
					xtea_crypted = false;
					state = ClientState::GAME;
				}
				else {
					state = ClientState::NONE;
				}
			}break;
			case ClientState::GAME:{
				if(!currenct_character.isValid()){
					state = ClientState::NONE;
					closeConnection();
				}
				packetType = incoming_packet.getUint8();
				switch(packetType){
					case 0x0A:
						return parseSelfAppear(incoming_packet);
					case 0x0B:
						return parseGMActions(incoming_packet);
					case 0x14:
						return parseErrorMessage(incoming_packet);
					case 0x15:
						return parseFYIMessage(incoming_packet);
					case 0x16:
						return parseWaitingList(incoming_packet);
					case 0x1E:
						return parsePing(incoming_packet);
					case 0x1F:
						return parseInit(incoming_packet);
					case 0x28:
						return parseDeath(incoming_packet);
					case 0x32:
						return parseCanReportBugs(incoming_packet);
					case 0x64:
						return parseMapDescription(incoming_packet);
					case 0x65:
						return parseMoveNorth(incoming_packet);
					case 0x66:
						return parseMoveEast(incoming_packet);
					case 0x67:
						return parseMoveSouth(incoming_packet);
					case 0x68:
						return parseMoveWest(incoming_packet);
					case 0x69:
						return parseUpdateTile(incoming_packet);
					case 0x6A:
						return parseTileAddThing(incoming_packet);
					case 0x6B:
						return parseTileTransformThing(incoming_packet);
					case 0x6C:
						return parseTileRemoveThing(incoming_packet);
					case 0x6D:
						return parseCreatureMove(incoming_packet);
					case 0x6E:
						return parseOpenContainer(incoming_packet);
					case 0x6F:
						return parseCloseContainer(incoming_packet);
					case 0x70:
						return parseContainerAddItem(incoming_packet);
					case 0x71:
						return parseContainerUpdateItem(incoming_packet);
					case 0x72:
						return parseContainerRemoveItem(incoming_packet);
					case 0x78:
						return parseInventorySetSlot(incoming_packet);
					case 0x79:
						return parseInventoryResetSlot(incoming_packet);
					case 0x7D:
						return parseSafeTradeRequestAck(incoming_packet);
					case 0x7E:
						return parseSafeTradeRequestNoAck(incoming_packet);
					case 0x7F:
						return parseSafeTradeClose(incoming_packet);
					case 0x82:
						return parseWorldLight(incoming_packet);
					case 0x83:
						return parseMagicEffect(incoming_packet);
					case 0x84:
						return parseAnimatedText(incoming_packet);
					case 0x85:
						return parseDistanceShot(incoming_packet);
					case 0x86:
						return parseCreatureSquare(incoming_packet);
					case 0x8C:
						return parseCreatureHealth(incoming_packet);
					case 0x8D:
						return parseCreatureLight(incoming_packet);
					case 0x8E:
						return parseCreatureOutfit(incoming_packet);
					case 0x8F:
						return parseCreatureSpeed(incoming_packet);
					case 0x90:
						return parseCreatureSkulls(incoming_packet);
					case 0x91:
						return parseCreatureShields(incoming_packet);
					case 0x92:
						return parseCreaturePassable(incoming_packet);
					case 0x96:
						return parseItemTextWindow(incoming_packet);
					case 0x97:
						return parseHouseTextWindow(incoming_packet);
					case 0xA0:
						return parsePlayerStats(incoming_packet);
					case 0xA1:
						return parsePlayerSkills(incoming_packet);
					case 0xA2:
						return parsePlayerIcons(incoming_packet);
					case 0xA3:
						return parsePlayerCancelAttack(incoming_packet);
					case 0xAA:
						return parseCreatureSpeak(incoming_packet);
					case 0xAB:
						return parseChannelList(incoming_packet);
					case 0xAC:
						return parseOpenChannel(incoming_packet);
					case 0xAD:
						return parseOpenPrivatePlayerChat(incoming_packet);
					case 0xAE:
						return parseOpenRuleViolation(incoming_packet);
					case 0xAF:
						return parseRuleViolationAF(incoming_packet);
					case 0xB0:
						return parseRuleViolationB0(incoming_packet);
					case 0xB1:
						return parseRuleViolationB1(incoming_packet);
					case 0xB2:
						return parseCreatePrivateChannel(incoming_packet);
					case 0xB3:
						return parseClosePrivateChannel(incoming_packet);
					case 0xB4:
						return parseTextMessage(incoming_packet);
					case 0xB5:
						return parsePlayerCancelWalk(incoming_packet);
					case 0xBE:
						return parseFloorChangeUp(incoming_packet);
					case 0xBF:
						return parseFloorChangeDown(incoming_packet);
					case 0xC8:
						return parseOutfitWindow(incoming_packet);
					case 0xD2:
						return parseVipState(incoming_packet);
					case 0xD3:
						return parseVipLogin(incoming_packet);
					case 0xD4:
						return parseVipLogout(incoming_packet);
					case 0xF0:
						return parseQuestList(incoming_packet);
					case 0xF1:
						return parseQuestPartList(incoming_packet);
					case 0x7A:
						return parseOpenShopWindow(incoming_packet);
					case 0x7B:
						return parsePlayerCash(incoming_packet);
					case 0x7C:
						return parseCloseShopWindow(incoming_packet);
					case 0xDC:
						return parseShowTutorial(incoming_packet);
					case 0xDD:
						return parseAddMapMarker(incoming_packet);
					default:
						cout<<"unknown packet type "<<packetType<<endl;
				}
			}break;
			case ClientState::INIT_GAME:{
				conn->addPacket(LoginPacket(login, password, version, os, dat_signature, spr_signature, pic_signature, rsa, xtea));
			}break;
		}
		break;
	}
}

int Client::tick(){
	if(conn == 0){
		return 1;
	}
	int st = conn->tick();
	if(st == 1){
		cout<<"socket error"<<endl;
		return 0;
	}
	else if(st == 2){
		if(conn->getPacket(incoming_packet)){
			idle();
		}
	}
	return 1;
}

void Client::parseSelfAppear(NetworkPacket& p){
	
}
void Client::parseGMActions(NetworkPacket& p){
	
}
void Client::parseErrorMessage(NetworkPacket& p){
	
}
void Client::parseFYIMessage(NetworkPacket& p){
	
}
void Client::parseWaitingList(NetworkPacket& p){
	
}
void Client::parsePing(NetworkPacket& p){
	
}
void Client::parseInit(NetworkPacket& p){
	if(p.getSize()>=5){
		for(int i=0;i<5;i++){
			verify_data[i] = p.getUint8();
		}
		state = ClientState::INIT_GAME;
	}
	else{
		state = ClientState::NONE;
	}
}
void Client::parseDeath(NetworkPacket& p){
	
}
void Client::parseCanReportBugs(NetworkPacket& p){
	
}
void Client::parseMapDescription(NetworkPacket& p){
	
}
void Client::parseMoveNorth(NetworkPacket& p){
	
}
void Client::parseMoveEast(NetworkPacket& p){
	
}
void Client::parseMoveSouth(NetworkPacket& p){
	
}
void Client::parseMoveWest(NetworkPacket& p){
	
}
void Client::parseUpdateTile(NetworkPacket& p){
	
}
void Client::parseTileAddThing(NetworkPacket& p){
	
}
void Client::parseTileTransformThing(NetworkPacket& p){
	
}
void Client::parseTileRemoveThing(NetworkPacket& p){
	
}
void Client::parseCreatureMove(NetworkPacket& p){
	
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
	
}
void Client::parseInventoryResetSlot(NetworkPacket& p){
	
}
void Client::parseSafeTradeRequestAck(NetworkPacket& p){
	
}
void Client::parseSafeTradeRequestNoAck(NetworkPacket& p){
	
}
void Client::parseSafeTradeClose(NetworkPacket& p){
	
}
void Client::parseWorldLight(NetworkPacket& p){
	
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
	
}
void Client::parseCreatureLight(NetworkPacket& p){
	
}
void Client::parseCreatureOutfit(NetworkPacket& p){
	
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