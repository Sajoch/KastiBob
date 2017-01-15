#ifndef __EXTENDCLIENT_HPP
#define __EXTENDCLIENT_HPP
#include "network.hpp"

class ExtendClient{
	class Client* c;
public:
	ExtendClient(class Client* _c);
	bool getMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t bz, int32_t w, int32_t h);
	bool getFloorMap(NetworkPacket& p, int32_t bx, int32_t by, int32_t _z, int32_t w, int32_t h);
	bool getSquareMap(NetworkPacket& p, int32_t _x, int32_t _y, int32_t _z);
	
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
};

#endif //__EXTENDCLIENT_HPP