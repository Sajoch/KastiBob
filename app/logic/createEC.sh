#!/bin/bash
dir="src/extendClient/"
files="parseErrorMessage parseFYIMessage parseWaitingList parsePing parseInit parseDeath parseCanReportBugs parseMapDescription parseMoveNorth parseMoveEast parseMoveSouth parseMoveWest parseUpdateTile parseTileAddThing parseTileTransformThing parseTileRemoveThing parseCreatureMove parseOpenContainer parseCloseContainer parseContainerAddItem parseContainerUpdateItem parseContainerRemoveItem parseInventorySetSlot parseInventoryResetSlot parseSafeTradeRequestAck parseSafeTradeRequestNoAck parseSafeTradeClose parseWorldLight parseMagicEffect parseAnimatedText parseDistanceShot parseCreatureSquare parseCreatureHealth parseCreatureLight parseCreatureOutfit parseCreatureSpeed parseCreatureSkulls parseCreatureShields parseCreaturePassable parseItemTextWindow parseHouseTextWindow parsePlayerStats parsePlayerSkills parsePlayerIcons parsePlayerCancelAttack parseCreatureSpeak parseChannelList parseOpenChannel parseOpenPrivatePlayerChat parseOpenRuleViolation parseRuleViolationAF parseRuleViolationB0 parseRuleViolationB1 parseCreatePrivateChannel parseClosePrivateChannel parseTextMessage parsePlayerCancelWalk parseFloorChangeUp parseFloorChangeDown parseOutfitWindow parseVipState parseVipLogin parseVipLogout parseQuestList parseQuestPartList parseOpenShopWindow parsePlayerCash parseCloseShopWindow parseShowTutorial parseAddMapMarker"
for f in $files; do
	body="#include \"../network.hpp\"\r\n#include \"../client.hpp\"\r\n\r\nvoid ExtendClient::$f(NetworkPacket& p){\r\n\t\r\n}"
	path=$f".cpp"
	if [ ! -f "$dir$path" ]; then
		echo -e $body > "$dir$path"
	fi
done