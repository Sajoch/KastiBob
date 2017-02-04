#include "client.hpp"
#include <iostream>
#include "packets/LoginPacket.hpp"
#include "packets/MovePacket.hpp"
#include "packets/OneBytePacket.hpp"
#include "extendClient.hpp"
#include "ground.hpp"
#include "network.hpp"
#include "datLoader.hpp"

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

Client::Client(string ip, uint16_t _version, uint16_t _os, string l, string p, DatLoader* dat):
	version(_version), os(_os),
	login(l), password(p)
{
	xtea = new XTEAcipher();
	rsa = new RSAcipher(rsa_m_n, rsa_e_n);
	ext = new ExtendClient(this);
	gMap = new Ground();
	datobjs = dat;
	
	conn = 0;
	clearCallbacks();	
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
	cout<<"new connection to "<<ip<<endl;
	conn = new NetworkManager(ip);
	conn->SetOnError([&](std::string msg){
		cout<<msg<<endl;
		errorHandler(msg, "NetworkError");
		disconnectHandler();
	});
	conn->SetOnPacketRecived([&](NetworkPacket& p){
		recv(p);
	});
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
void Client::afterError(std::function<void(std::string, std::string)> cb){
	errorHandler = cb;
}
void Client::afterDisconnect(std::function<void(void)> cb){
	disconnectHandler = cb;
}
void Client::clearCallbacks(){
	afterRecvFunc = [](){};
	changeStateFunc = [](int, std::string){};
	errorHandler = [](std::string msg, std::string){
		cout<<"Error: "<<msg<<endl;
	};
	disconnectHandler = [](){};
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
			return true;
		} else {
			disconnect("No valid character to enter game");
			return false;
		}
	}
	return false;
}
void Client::enter(){
	newConnection(current_character.getAddress());
	current_character.show();
	xtea_crypted = false;
	state = ClientState::GAME;
	last_ping = std::chrono::system_clock::now();
}

void Client::recv(NetworkPacket& p){
	if(xtea_crypted){
		p.xteaDecrypt(xtea);
	}
	uint16_t len = p.getUint16();
	uint16_t real_len = p.getSize();
	if(real_len < len){
		cout<<"wrong size after XTea decrypt, expected "<<len<<" but has "<<real_len<<endl;
		return;
	}
	p.resize(len);
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
				do{
					packetType = p.getUint8();
					//cout<<"recv "<<packetType<<endl;
					switch(packetType){
						case 0x0A:{ //Error message
							std::string errormsg = p.getTString();
							changeStateFunc(2, errormsg);
							disconnect("error in login "+errormsg);
						}break;
						case 0x0B:{ //For your information
							std::string infomsg = p.getTString();
							cout<<"Info: "<<infomsg<<endl;
						}break;
						case 0x14:{ //MOTD
							std::string motd = p.getTString();
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
							uint16_t nchars = p.getUint8();
							for(uint32_t i = 0; i < nchars; ++i){
								std::string charName = p.getTString();
								std::string world = p.getTString();
								uint32_t ip = p.getUint32();
								uint16_t port = p.getUint16();
								characters.push_back(Character(charName, world, ip, port));
							}
							premiumDays = p.getUint16();
							state = ClientState::WAIT_TO_ENTER;
						}break;
					}
				}while(p.getSize()>=1);
				if(state != ClientState::NONE){
					continue;
				}
				closeConnection();
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
				packetType = p.getUint8();
				cout<<"packet "<<packetType<<endl;
				switch(packetType){
					case 0x0A:
						ext->SelfAppear(p);
						break;
					/*case 0x0B:
						ext->GMActions(p);
						break;
					*/
					case 0x14:
						ext->ErrorMessage(p);
						break;
					/*case 0x15:
						ext->FYIMessage(p);
						break;
					case 0x16:
						ext->WaitingList(p);
						break;
					*/
					case 0x1E:
						ext->Ping(p);
						break;
					case 0x1F:
						ext->Init(p);
						break;
					/*case 0x28:
						ext->Death(p);
						break;
					case 0x32:
						ext->CanReportBugs(p);
						break;
					*/
					case 0x64:
						ext->MapDescription(p);
						break;
					case 0x65:
						ext->MoveNorth(p);
						break;
					case 0x66:
						ext->MoveEast(p);
						break;
					case 0x67:
						ext->MoveSouth(p);
						break;
					case 0x68:
						ext->MoveWest(p);
						break;
					/*case 0x69:
						ext->UpdateTile(p);
						break;*/
					case 0x6A:
						ext->TileAddThing(p);
						break;
					/*case 0x6B:
						ext->TileTransformThing(p);
						break;*/
					case 0x6C:
						ext->TileRemoveThing(p);
						break;
					case 0x6D:
						ext->CreatureMove(p);
						break;
					/*case 0x6E:
						ext->OpenContainer(p);
						break;
					case 0x6F:
						ext->CloseContainer(p);
						break;
					case 0x70:
						ext->ContainerAddItem(p);
						break;
					case 0x71:
						ext->ContainerUpdateItem(p);
						break;
					case 0x72:
						ext->ContainerRemoveItem(p);
						break;
					*/
					case 0x78:
						ext->InventorySetSlot(p);
						break;
					case 0x79:
						ext->InventoryResetSlot(p);
						break;
					/*case 0x7D:
						ext->SafeTradeRequestAck(p);
						break;
					case 0x7E:
						ext->SafeTradeRequestNoAck(p);
						break;
					case 0x7F:
						ext->SafeTradeClose(p);
						break;
					*/
					case 0x82:
						ext->WorldLight(p);
						break;
					case 0x83:
						ext->MagicEffect(p);
						break;
					/*case 0x84:
						ext->AnimatedText(p);
						break;
					case 0x85:
						ext->DistanceShot(p);
						break;
					case 0x86:
						ext->CreatureSquare(p);
						break;
					*/
					case 0x8C:
						ext->CreatureHealth(p);
						break;
					case 0x8D:
						ext->CreatureLight(p);
						break;
					/*case 0x8E:
						ext->CreatureOutfit(p);
						break;
					case 0x8F:
						ext->CreatureSpeed(p);
						break;
					case 0x90:
						ext->CreatureSkulls(p);
						break;
					case 0x91:
						ext->CreatureShields(p);
						break;
					case 0x92:
						ext->CreaturePassable(p);
						break;
					case 0x96:
						ext->ItemTextWindow(p);
						break;
					case 0x97:
						ext->HouseTextWindow(p);
						break;*/
					case 0xA0:
						ext->PlayerStats(p);
						break;
					case 0xA1:
						ext->PlayerSkills(p);
						break;
					case 0xA2:
						ext->PlayerIcons(p);
						break;/*
					case 0xA3:
						ext->PlayerCancelAttack(p);
						break;
					*/
					case 0xAA:
						ext->CreatureSpeak(p);
						break;
					/*case 0xAB:
						ext->ChannelList(p);
						break;
					case 0xAC:
						ext->OpenChannel(p);
						break;
					case 0xAD:
						ext->OpenPrivatePlayerChat(p);
						break;
					case 0xAE:
						ext->OpenRuleViolation(p);
						break;
					case 0xAF:
						ext->RuleViolationAF(p);
						break;
					case 0xB0:
						ext->RuleViolationB0(p);
						break;
					case 0xB1:
						ext->RuleViolationB1(p);
						break;
					case 0xB2:
						ext->CreatePrivateChannel(p);
						break;
					case 0xB3:
						ext->ClosePrivateChannel(p);
						break;
					*/
					case 0xB4:
						ext->TextMessage(p);
						break;
					case 0xB5:
						ext->PlayerCancelWalk(p);
						break;
					/*case 0xBE:
						ext->FloorChangeUp(p);
						break;
					case 0xBF:
						ext->FloorChangeDown(p);
						break;
					case 0xC8:
						ext->OutfitWindow(p);
						break;
					case 0xD2:
						ext->VipState(p);
						break;
					case 0xD3:
						ext->VipLogin(p);
						break;
					case 0xD4:
						ext->VipLogout(p);
						break;
					case 0xF0:
						ext->QuestList(p);
						break;
					case 0xF1:
						ext->QuestPartList(p);
						break;
					case 0x7A:
						ext->OpenShopWindow(p);
						break;
					case 0x7B:
						ext->PlayerCash(p);
						break;
					case 0x7C:
						ext->CloseShopWindow(p);
						break;
					case 0xDC:
						ext->ShowTutorial(p);
						break;
					case 0xDD:
						ext->AddMapMarker(p);
						break;
					*/
					default:
						cout<<"unknown packet type "<<packetType<<endl;
						p.dump();
						errorHandler(to_string(packetType), "NetworkParser");
						exit(1);
						return;
				}
				if(p.getSize()>0){
					continue;
				}
			}break;
		}
		break;
	}
	afterRecvFunc();
}

uint32_t Client::getMapViewX(){
	return mapViewX;
}
uint32_t Client::getMapViewY(){
	return mapViewY;
}
bool Client::getGroundSquare(Item& it, uint32_t cx, uint32_t cy){
	Square& sq = gMap->getSquare(cx, cy, z);
	return sq.getGround(it);
}
void Client::move(ClientDirectory dir){
	if(conn == 0){
		return;
	}
	conn->addPacket(MovePacket(dir, xtea));
}
void Client::sendLogout(){
	if(conn == 0){
		return;
	}
	conn->addPacket(OneBytePacket(0x14, xtea));
}
void Client::disconnect(std::string reason){
	state = ClientState::NONE;
	closeConnection();
	errorHandler(reason, "Disconnect");
}