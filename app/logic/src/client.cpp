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
				void(ExtendClient::*cb_ret)(NetworkPacket& p);
				std::string function_name;
				if(ext->getCallback(cb_ret, function_name, packetType)){
					(ext->*cb_ret)(p);
					cout<<"called "<<function_name<<endl;
				}else{
					if(!function_name.empty()){
						cout<<"unimplemented callback "<<function_name<<endl;
					}else{
						cout<<"unknown packet type "<<packetType<<endl;
					}
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

int32_t Client::getMapViewX(){
	return mapViewX;
}
int32_t Client::getMapViewY(){
	return mapViewY;
}
Square& Client::getSquare(int32_t cx, int32_t cy){
	return gMap->getSquare(cx, cy);
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