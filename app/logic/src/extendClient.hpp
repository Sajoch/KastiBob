#ifndef __EXTENDCLIENT_HPP
#define __EXTENDCLIENT_HPP
#include <cinttypes>

class ExtendClient{
	class Client* c;
	bool getMap(class NetworkPacket& p, int32_t bx, int32_t by, int32_t bz, int32_t w, int32_t h);
	bool getFloorMap(class NetworkPacket& p, int32_t bx, int32_t by, int32_t _z, int32_t w, int32_t h, int32_t& skipTiles);
	bool getSquareMap(class NetworkPacket& p, int32_t _x, int32_t _y, int32_t _z);
public:
	ExtendClient(class Client* _c);
	void SelfAppear(class NetworkPacket& p);
	void GMActions(class NetworkPacket& p);
	void ErrorMessage(class NetworkPacket& p);
	void FYIMessage(class NetworkPacket& p);
	void WaitingList(class NetworkPacket& p);
	void Ping(class NetworkPacket& p);
	void Init(class NetworkPacket& p);
	void Death(class NetworkPacket& p);
	void CanReportBugs(class NetworkPacket& p);
	void MapDescription(class NetworkPacket& p);
	void MoveNorth(class NetworkPacket& p);
	void MoveEast(class NetworkPacket& p);
	void MoveSouth(class NetworkPacket& p);
	void MoveWest(class NetworkPacket& p);
	void UpdateTile(class NetworkPacket& p);
	void TileAddThing(class NetworkPacket& p);
	void TileTransformThing(class NetworkPacket& p);
	void TileRemoveThing(class NetworkPacket& p);
	void CreatureMove(class NetworkPacket& p);
	void OpenContainer(class NetworkPacket& p);
	void CloseContainer(class NetworkPacket& p);
	void ContainerAddItem(class NetworkPacket& p);
	void ContainerUpdateItem(class NetworkPacket& p);
	void ContainerRemoveItem(class NetworkPacket& p);
	void InventorySetSlot(class NetworkPacket& p);
	void InventoryResetSlot(class NetworkPacket& p);
	void SafeTradeRequestAck(class NetworkPacket& p);
	void SafeTradeRequestNoAck(class NetworkPacket& p);
	void SafeTradeClose(class NetworkPacket& p);
	void WorldLight(class NetworkPacket& p);
	void MagicEffect(class NetworkPacket& p);
	void AnimatedText(class NetworkPacket& p);
	void DistanceShot(class NetworkPacket& p);
	void CreatureSquare(class NetworkPacket& p);
	void CreatureHealth(class NetworkPacket& p);
	void CreatureLight(class NetworkPacket& p);
	void CreatureOutfit(class NetworkPacket& p);
	void CreatureSpeed(class NetworkPacket& p);
	void CreatureSkulls(class NetworkPacket& p);
	void CreatureShields(class NetworkPacket& p);
	void CreaturePassable(class NetworkPacket& p);
	void ItemTextWindow(class NetworkPacket& p);
	void HouseTextWindow(class NetworkPacket& p);
	void PlayerStats(class NetworkPacket& p);
	void PlayerSkills(class NetworkPacket& p);
	void PlayerIcons(class NetworkPacket& p);
	void PlayerCancelAttack(class NetworkPacket& p);
	void CreatureSpeak(class NetworkPacket& p);
	void ChannelList(class NetworkPacket& p);
	void OpenChannel(class NetworkPacket& p);
	void OpenPrivatePlayerChat(class NetworkPacket& p);
	void OpenRuleViolation(class NetworkPacket& p);
	void RuleViolationAF(class NetworkPacket& p);
	void RuleViolationB0(class NetworkPacket& p);
	void RuleViolationB1(class NetworkPacket& p);
	void CreatePrivateChannel(class NetworkPacket& p);
	void ClosePrivateChannel(class NetworkPacket& p);
	void TextMessage(class NetworkPacket& p);
	void PlayerCancelWalk(class NetworkPacket& p);
	void FloorChangeUp(class NetworkPacket& p);
	void FloorChangeDown(class NetworkPacket& p);
	void OutfitWindow(class NetworkPacket& p);
	void VipState(class NetworkPacket& p);
	void VipLogin(class NetworkPacket& p);
	void VipLogout(class NetworkPacket& p);
	void QuestList(class NetworkPacket& p);
	void QuestPartList(class NetworkPacket& p);
	void OpenShopWindow(class NetworkPacket& p);
	void PlayerCash(class NetworkPacket& p);
	void CloseShopWindow(class NetworkPacket& p);
	void ShowTutorial(class NetworkPacket& p);
	void AddMapMarker(class NetworkPacket& p);
};

#endif //__EXTENDCLIENT_HPP