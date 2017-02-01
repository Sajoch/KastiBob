#ifndef __CLIENT_HPP
#define __CLIENT_HPP

#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include "dll.h"
//#include "cipher.hpp"
//#include "packet.hpp"
//#include "network.hpp"
//#include "utils.hpp"
#include "creature.hpp"
//#include "ground.hpp"
//#include "outfit.hpp"
//#include "extendClient.hpp"

class API Character{
	std::string nick;
	std::string world;
	uint16_t oip[4];
	uint16_t port;
	bool valid;
public:
	Character();
	Character(std::string _nick, std::string _world, uint32_t _ip, uint16_t _port);
	bool isValid();
	std::string getAddress();
	std::string getName();
	void show();
};

class Client_Skill{
public:
	uint16_t val;
	uint16_t percent;
};

class API Client: public Creature{
	friend class ExtendClient;
	class XTEAcipher* xtea;
	class RSAcipher* rsa;
	static const char* rsa_e_n;
	static const char* rsa_m_n;
	static uint32_t dat_signature;
	static uint32_t spr_signature;
	static uint32_t pic_signature;
	static uint32_t mapViewX;
	static uint32_t mapViewY;
	static int32_t mapLayers;
	ClientState state;
	class ExtendClient* ext;

	Character current_character;
	std::vector<Character> characters;
	uint16_t premiumDays;

	uint16_t drawSpeed;
	bool canReportBugs;
	std::function<void(int, std::string)> changeStateFunc;
	std::function<void(std::string)> errorHandler;
	std::function<void(void)> afterRecvFunc;
	class Ground* gMap;
	
	uint16_t health;
	uint16_t max_health;
	uint32_t free_cap;
	uint64_t experience;
	uint16_t level;
	uint16_t percent_level;
	uint16_t mana;
	uint16_t max_mana;
	uint16_t magic_level;
	uint16_t magic_level_percent;
	uint16_t soul;
	uint16_t stamina;
	uint16_t icons;
	
	Client_Skill skills[7];

	uint8_t verify_data[5];
	uint16_t version;
	uint16_t os;
	std::string login;
	std::string password;
	class NetworkManager* conn;
	bool xtea_crypted;
	void newConnection(std::string ip);
	void disconnect(std::string reason);
	void closeConnection();
	void recv(NetworkPacket& p);
	
public:
	void move(ClientDirectory dir);
	Client(std::string ip, uint16_t _version, uint16_t _os, std::string l, std::string p, class DatLoader* dat);
	~Client();
	int tick();
	void loginListener(std::function<void(int, std::string)> cb);
	void loginListener();
	void listChars(std::function<void(std::string, size_t)> cb);
	void afterError(std::function<void(std::string)> cb);
	void afterRecv(std::function<void(void)> cb);
	void afterRecv();
	bool setChar(size_t id);
	void enter();
	void sendLogout();
};
#endif
