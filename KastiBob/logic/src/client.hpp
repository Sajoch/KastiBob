#ifndef __CLIENT_HPP
#define __CLIENT_HPP

#include <string>
#include <vector>
#include "cipher.hpp"
#include "packet.hpp"
#include "network.hpp"
#include "utils.hpp"
#include <chrono>
#include "ground.hpp"
#include "outfit.hpp"

class Character{
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
};

class Client{
	XTEAcipher xtea;
	RSAcipher rsa;
	static const char* rsa_e_n;
	static const char* rsa_m_n;
	static uint32_t dat_signature;
	static uint32_t spr_signature;
	static uint32_t pic_signature;
	static uint32_t mapViewX;
	static uint32_t mapViewY;
	ClientState state;

	Character currenct_character;
	std::vector<Character> characters;
	uint16_t premiumDays;

	uint16_t drawSpeed;
	uint32_t id;
	bool canReportBugs;
	std::chrono::seconds AntyIdle_duration;
	std::chrono::system_clock::time_point lastAntyIdle;
	Ground gMap;
	uint32_t x;
	uint32_t y;
	uint32_t z;
	Outfit apperance;
	ClientDirectory dir;

	uint8_t verify_data[5];
	NetworkPacket incoming_packet;
	uint16_t version;
	uint16_t os;
	std::string login;
	std::string password;
	NetworkManager* conn;
	bool xtea_crypted;
	void newConnection(std::string ip);
	void closeConnection();
	void recv();
	void idle();

	void parseSelfAppear(NetworkPacket& p);
	void parseGMActions(NetworkPacket& p);
	void parseErrorMessage(NetworkPacket& p);
	void parseFYIMessage(NetworkPacket& p);
	void parseWaitingList(NetworkPacket& p);
	void parsePing(NetworkPacket& p);
	void parseInit(NetworkPacket& p);
	void parseDeath(NetworkPacket& p);
	void parseCanReportBugs(NetworkPacket& p);
	void parseMapDescription(NetworkPacket& p);
	void parseMoveNorth(NetworkPacket& p);
	void parseMoveEast(NetworkPacket& p);
	void parseMoveSouth(NetworkPacket& p);
	void parseMoveWest(NetworkPacket& p);
	void parseUpdateTile(NetworkPacket& p);
	void parseTileAddThing(NetworkPacket& p);
	void parseTileTransformThing(NetworkPacket& p);
	void parseTileRemoveThing(NetworkPacket& p);
	void parseCreatureMove(NetworkPacket& p);
	void parseOpenContainer(NetworkPacket& p);
	void parseCloseContainer(NetworkPacket& p);
	void parseContainerAddItem(NetworkPacket& p);
	void parseContainerUpdateItem(NetworkPacket& p);
	void parseContainerRemoveItem(NetworkPacket& p);
	void parseInventorySetSlot(NetworkPacket& p);
	void parseInventoryResetSlot(NetworkPacket& p);
	void parseSafeTradeRequestAck(NetworkPacket& p);
	void parseSafeTradeRequestNoAck(NetworkPacket& p);
	void parseSafeTradeClose(NetworkPacket& p);
	void parseWorldLight(NetworkPacket& p);
	void parseMagicEffect(NetworkPacket& p);
	void parseAnimatedText(NetworkPacket& p);
	void parseDistanceShot(NetworkPacket& p);
	void parseCreatureSquare(NetworkPacket& p);
	void parseCreatureHealth(NetworkPacket& p);
	void parseCreatureLight(NetworkPacket& p);
	void parseCreatureOutfit(NetworkPacket& p);
	void parseCreatureSpeed(NetworkPacket& p);
	void parseCreatureSkulls(NetworkPacket& p);
	void parseCreatureShields(NetworkPacket& p);
	void parseCreaturePassable(NetworkPacket& p);
	void parseItemTextWindow(NetworkPacket& p);
	void parseHouseTextWindow(NetworkPacket& p);
	void parsePlayerStats(NetworkPacket& p);
	void parsePlayerSkills(NetworkPacket& p);
	void parsePlayerIcons(NetworkPacket& p);
	void parsePlayerCancelAttack(NetworkPacket& p);
	void parseCreatureSpeak(NetworkPacket& p);
	void parseChannelList(NetworkPacket& p);
	void parseOpenChannel(NetworkPacket& p);
	void parseOpenPrivatePlayerChat(NetworkPacket& p);
	void parseOpenRuleViolation(NetworkPacket& p);
	void parseRuleViolationAF(NetworkPacket& p);
	void parseRuleViolationB0(NetworkPacket& p);
	void parseRuleViolationB1(NetworkPacket& p);
	void parseCreatePrivateChannel(NetworkPacket& p);
	void parseClosePrivateChannel(NetworkPacket& p);
	void parseTextMessage(NetworkPacket& p);
	void parsePlayerCancelWalk(NetworkPacket& p);
	void parseFloorChangeUp(NetworkPacket& p);
	void parseFloorChangeDown(NetworkPacket& p);
	void parseOutfitWindow(NetworkPacket& p);
	void parseVipState(NetworkPacket& p);
	void parseVipLogin(NetworkPacket& p);
	void parseVipLogout(NetworkPacket& p);
	void parseQuestList(NetworkPacket& p);
	void parseQuestPartList(NetworkPacket& p);
	void parseOpenShopWindow(NetworkPacket& p);
	void parsePlayerCash(NetworkPacket& p);
	void parseCloseShopWindow(NetworkPacket& p);
	void parseShowTutorial(NetworkPacket& p);
	void parseAddMapMarker(NetworkPacket& p);

public:
	void move(ClientDirectory dir);
	Client(std::string ip, uint16_t _version, uint16_t _os, std::string l, std::string p);
	int tick();
};
#endif
