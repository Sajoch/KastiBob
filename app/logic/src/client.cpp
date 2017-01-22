#include "client.hpp"
#include <iostream>
#include "packets/LoginPacket.hpp"
#include "packets/MovePacket.hpp"
#include "packets/OneBytePacket.hpp"
#include "extendClient.hpp"
#include "ground.hpp"
#include "network.hpp"
/*
#include "packets/PingPacket.hpp"
*/
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
void Character::show(){
	cout<<"Nick: "<<nick<<" on "<<getAddress()<<endl;
}

Client::Client(string ip, uint16_t _version, uint16_t _os, string l, string p):
	version(_version), os(_os),
	login(l), password(p)
{
	xtea = new XTEAcipher();
	rsa = new RSAcipher(rsa_m_n, rsa_e_n);
	ext = new ExtendClient(this);
	gMap = new Ground();
	incoming_packet = new NetworkPacket();
	
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
	cout<<"destoring client"<<endl;
}
void Client::newConnection(std::string ip){
	if(conn != 0){
		closeConnection();
		cout<<"close last connection"<<endl;
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
			cout<<"setChar disconnect"<<endl;
		}
		current_character = Character();
		state = ClientState::WAIT_TO_ENTER;
	}else if(id<characters.size()){
		current_character = characters[id];
		if (current_character.isValid()){
			newConnection(current_character.getAddress());
			current_character.show();
			xtea_crypted = false;
			state = ClientState::GAME;
			return true;
		} else {
			disconnect("No valid character to enter game");
			return false;
		}
	}
	return false;
}
void Client::recv(){
	if(xtea_crypted){
		incoming_packet->xteaDecrypt(xtea);
	}
	uint16_t len = incoming_packet->getUint16();
	uint16_t real_len = incoming_packet->getSize();
	if(real_len < len){
		cout<<"wrong size after XTea decrypt, expected "<<len<<" but has "<<real_len<<endl;
		return;
	}
	incoming_packet->resize(len);
	uint16_t packetType;
	while(true){
		switch(state){
			case ClientState::NONE:{
				closeConnection();
				cout<<"none disconnect"<<endl;
				changeStateFunc(3, "");
			}break;
			case ClientState::LOGIN:{
				state = ClientState::NONE;
				cout<<"login start disconnect"<<endl;
				closeConnection();
				do{
					packetType = incoming_packet->getUint8();
					switch(packetType){
						case 0x0A:{ //Error message
							std::string errormsg = incoming_packet->getTString();
							changeStateFunc(2, errormsg);
							disconnect("error in login "+errormsg);
						}break;
						case 0x0B:{ //For your information
							std::string infomsg = incoming_packet->getTString();
							cout<<"Info: "<<infomsg<<endl;
						}break;
						case 0x14:{ //MOTD
							std::string motd = incoming_packet->getTString();
							cout<<"Motd "<<motd<<endl;
						}break;
						case 0x1E: //Patching exe/dat/spr messages
						case 0x1F:
						case 0x20:
							changeStateFunc(2, "need to patch");
							disconnect("need to patch in login");
							return;
						break;
						case 0x28: //Select other login server
							changeStateFunc(2, "Select other login server");
							disconnect("select other login server in login");
							return;
						break;
						case 0x64:{ //character list
							uint16_t nchars = incoming_packet->getUint8();
							for(uint32_t i = 0; i < nchars; ++i){
								std::string charName = incoming_packet->getTString();
								std::string world = incoming_packet->getTString();
								uint32_t ip = incoming_packet->getUint32();
								uint16_t port = incoming_packet->getUint16();
								characters.push_back(Character(charName, world, ip, port));
							}
							premiumDays = incoming_packet->getUint16();
							state = ClientState::WAIT_TO_ENTER;
						}break;
					}
				}while(incoming_packet->getSize()>=1);
				if(state != ClientState::NONE){
					continue;
				}
			}break;
			case ClientState::WAIT_TO_ENTER:
				changeStateFunc(4, "");
				cout<<"wait"<<endl;
			break;
			case ClientState::ENTER_GAME:{
				if (current_character.isValid() && characters.size()>0){
					newConnection(current_character.getAddress());
					xtea_crypted = false;
					state = ClientState::GAME;
					cout<<"enter to game"<<endl;
				}
				else {
					cout<<"no valid"<<endl;
					disconnect("no valid character in enter game");
				}
			}break;
			case ClientState::GAME:{
				if(!current_character.isValid()){
					disconnect("no valid character in game");
				}
				packetType = incoming_packet->getUint8();
				cout<<"packet "<<packetType<<endl;
				switch(packetType){
					case 0x0A:
						ext->SelfAppear(incoming_packet);
					break;
					/*case 0x0B:
						ext->GMActions(incoming_packet);
					break;
					*/
					case 0x14:
						ext->ErrorMessage(incoming_packet);
					break;
					/*case 0x15:
						ext->FYIMessage(incoming_packet);
					break;
					case 0x16:
						ext->WaitingList(incoming_packet);
					break;
					*/
					case 0x1E:
						ext->Ping(incoming_packet);
					break;
					case 0x1F:
						ext->Init(incoming_packet);
					break;
					/*case 0x28:
						ext->Death(incoming_packet);
					break;
					case 0x32:
						ext->CanReportBugs(incoming_packet);
					break;
					*/
					case 0x64:
						ext->MapDescription(incoming_packet);
					break;
					case 0x65:
						ext->MoveNorth(incoming_packet);
					break;
					case 0x66:
						ext->MoveEast(incoming_packet);
					break;
					case 0x67:
						ext->MoveSouth(incoming_packet);
					break;
					case 0x68:
						ext->MoveWest(incoming_packet);
					break;
					/*case 0x69:
						ext->UpdateTile(incoming_packet);
					break;*/
					case 0x6A:
						ext->TileAddThing(incoming_packet);
					break;
					/*case 0x6B:
						ext->TileTransformThing(incoming_packet);
					break;
					case 0x6C:
						ext->TileRemoveThing(incoming_packet);
					break;*/
					case 0x6D:
						ext->CreatureMove(incoming_packet);
					break;
					/*case 0x6E:
						ext->OpenContainer(incoming_packet);
					break;
					case 0x6F:
						ext->CloseContainer(incoming_packet);
					break;
					case 0x70:
						ext->ContainerAddItem(incoming_packet);
					break;
					case 0x71:
						ext->ContainerUpdateItem(incoming_packet);
					break;
					case 0x72:
						ext->ContainerRemoveItem(incoming_packet);
					break;
					*/
					case 0x78:
						ext->InventorySetSlot(incoming_packet);
					break;
					case 0x79:
						ext->InventoryResetSlot(incoming_packet);
					break;
					/*case 0x7D:
						ext->SafeTradeRequestAck(incoming_packet);
					break;
					case 0x7E:
						ext->SafeTradeRequestNoAck(incoming_packet);
					break;
					case 0x7F:
						ext->SafeTradeClose(incoming_packet);
					break;
					*/
					case 0x82:
						ext->WorldLight(incoming_packet);
					break;
					case 0x83:
						ext->MagicEffect(incoming_packet);
					break;
					/*case 0x84:
						ext->AnimatedText(incoming_packet);
					break;
					case 0x85:
						ext->DistanceShot(incoming_packet);
					break;
					case 0x86:
						ext->CreatureSquare(incoming_packet);
					break;
					*/
					case 0x8C:
						ext->CreatureHealth(incoming_packet);
					break;
					case 0x8D:
						ext->CreatureLight(incoming_packet);
					break;
					/*case 0x8E:
						ext->CreatureOutfit(incoming_packet);
					break;
					case 0x8F:
						ext->CreatureSpeed(incoming_packet);
					break;
					case 0x90:
						ext->CreatureSkulls(incoming_packet);
					break;
					case 0x91:
						ext->CreatureShields(incoming_packet);
					break;
					case 0x92:
						ext->CreaturePassable(incoming_packet);
					break;
					case 0x96:
						ext->ItemTextWindow(incoming_packet);
					break;
					case 0x97:
						ext->HouseTextWindow(incoming_packet);
					break;
					case 0xA0:
						ext->PlayerStats(incoming_packet);
					break;
					case 0xA1:
						ext->PlayerSkills(incoming_packet);
					break;
					case 0xA2:
						ext->PlayerIcons(incoming_packet);
					break;
					case 0xA3:
						ext->PlayerCancelAttack(incoming_packet);
					break;
					*/
					case 0xAA:
						ext->CreatureSpeak(incoming_packet);
					break;
					/*case 0xAB:
						ext->ChannelList(incoming_packet);
					case 0xAC:
						ext->OpenChannel(incoming_packet);
					break;
					case 0xAD:
						ext->OpenPrivatePlayerChat(incoming_packet);
					break;
					case 0xAE:
						ext->OpenRuleViolation(incoming_packet);
					break;
					case 0xAF:
						ext->RuleViolationAF(incoming_packet);
					break;
					case 0xB0:
						ext->RuleViolationB0(incoming_packet);
					break;
					case 0xB1:
						ext->RuleViolationB1(incoming_packet);
					break;
					case 0xB2:
						ext->CreatePrivateChannel(incoming_packet);
					break;
					case 0xB3:
						ext->ClosePrivateChannel(incoming_packet);
					break;
					*/
					case 0xB4:
						ext->TextMessage(incoming_packet);
					break;
					/*case 0xB5:
						ext->PlayerCancelWalk(incoming_packet);
					break;
					case 0xBE:
						ext->FloorChangeUp(incoming_packet);
					break;
					case 0xBF:
						ext->FloorChangeDown(incoming_packet);
					break;
					case 0xC8:
						ext->OutfitWindow(incoming_packet);
					break;
					case 0xD2:
						ext->VipState(incoming_packet);
					break;
					case 0xD3:
						ext->VipLogin(incoming_packet);
					break;
					case 0xD4:
						ext->VipLogout(incoming_packet);
					break;
					case 0xF0:
						ext->QuestList(incoming_packet);
					break;
					case 0xF1:
						ext->QuestPartList(incoming_packet);
					break;
					case 0x7A:
						ext->OpenShopWindow(incoming_packet);
					break;
					case 0x7B:
						ext->PlayerCash(incoming_packet);
					break;
					case 0x7C:
						ext->CloseShopWindow(incoming_packet);
					break;
					case 0xDC:
						ext->ShowTutorial(incoming_packet);
					break;
					case 0xDD:
						ext->AddMapMarker(incoming_packet);
					break;
					*/
					default:
						cout<<"unknown packet type "<<packetType<<endl;
						incoming_packet->dump();
						return;
				}
				if(incoming_packet->getSize()>0){
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

void Client::move(ClientDirectory dir){
	conn->addPacket(MovePacket(dir, xtea));
}
void Client::sendLogout(){
	if(conn == 0){
		disconnect("sendLogout connection is null");
		return;
	}
	conn->addPacket(OneBytePacket(0x14, xtea));
}
void Client::disconnect(std::string reason){
	state = ClientState::NONE;
	closeConnection();
	cout<<"disconnect: "<<reason<<endl;
}