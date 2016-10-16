// ladne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	https://otland.net/threads/tibia-8-0-address-list.235/
	do nich dodac 0x27440


	<ZAJEBISCIE WAZNE INFO>
	0x00392E50 //if connected 8 else 0

	
	ping	0x100300A8	lub		0x10028100


	<ACCOUNT>(string)
	acc_name	0x00792E2C
	password	0x00792E0C


	<CHARACTER INFO>
	Player_ID 			00x0635F10
	Stamina 			0x00635EE4	 - max to 3360minut czyli 56 godzin
	max hp				0x00635F0C
	hp					0x00635F0C
	max mana			0x00635EEC
	mana				0x00635EF0
	lvl					0x00635F00
	% lvl				0x00635EF8
	exp					0x00635F04
	exp/h				0x006404A4
	soul				0x00635EE8
	cap					0x00635EE0


	<SKILLS>
	magic lvl			0x00635EFC
	fist fighting		0x00635EB8
	club fighting		0x00635EBC
	sword fighting		0x00635EC0
	axe figting			0x00635EC4
	distance fighting	0x00635EC8
	shielding			0x00635ECC
	fishing				0x00635ED0

	MagicPerc		0x00635EF4
	FistPerc		0x00635E9C
	ClubPerc		0x00635EA0
	SwordPerc		0x00635EA4
	AxePerc			0x00635EA8
	DistnacePerc	0x00635EAC
	ShieldingPerc	0x00635EB0
	PFishingPerc	0x00635EB4


	<XYZ>
	x		0x00645538
	y		0x00645534
	z		0x00645530
	goto x	0x00792E8C
	goto y	0x00635F50


	<EQ> 0 if unequipped else id item
	helm		0x00642BC8
	klata		0x00642BEC
	spodnie		0x00642C10
	buty		0x00642C1C
	lewa reka	0x00642C04
	prawa reka	0x00642BF8
	amulet		0x00642BD4
	pierscien	0x00642C28
	plecak		0x00642BE0
	arrow slot	0x00642C34

	SLOT_RIGHT_COUNT	0x0063E3FC
	SLOT_LEFT_COUNT		0x0063E408
	SLOT_AMMO_COUNT		0x0063E438


	<ID>
	ostatni przenoszony item id -		 0x00792EF0
	last used item id -					 0x00792F08
	last used item id lub 99 if player - 0x00792EFC


	<BEZUZYTECZNE LUB INNE>
	0 jak nic, 11 jak wlaczone menu, 12 jak context menu -	 0x00792EB0
	jak to wyzej 11 to pokazuje tytul -						 0x00000050
	ostatnia wiadomosc na chat (czasami?)(string) -			 0x007D6928

	Battlelist_Begin = 0x00635F70
	Battlelist_End =	0x0063BD30

	
	'' in-game
	IS_INGAME = 0x0078E238
	
	'' current window
	CURRENT_WINDOW = 0x00640CF4

	'' map
	MAP_POINTER = 0x00645848

	'' container
	CONTAINER_BEGIN =	0x0063E440
	CONTAINER_END =		0x00640300

	'' statusbar
	STATUSBAR_TEXT (string) - 0x007D66D8
	STATUSBAR_TIMER			  0x007D66D4
	
	'' level spy
	LEVELSPY_NOP = 0x004EB760
	LEVELSPY_ABOVE = 0x004EB75C
	LEVELSPY_BELOW = 0x004EB764

	'' name spy
	NAME_SPY = 0x00504717
	NAME_SPY_EX = 0x00504A21

	'' left-click
	CLICK_ID =		0x0078E2D4
	CLICK_COUNT =	0x0078E2D8
	CLICK_Z =		0x0078E26C

	'' see (inspect)
	SEE_ID =		0x0078E5E0
	SEE_COUNT =		0x0078E2E4
	SEE_Z =			0x0078E240
	
	'' mouse (fishing)
	MOUSE_ID = 0x0078E298

	'' target
	TARGET_ID =				0x00635EDC
	TARGET_TYPE =			0x00635EDF
	TARGET_BATTLELIST_ID =	0x00635ED4
	TARGET_BATTLELIST_TYPE =0x00635ED7
	

	<PLAYER FLAG>
	0x00635E98
	(wartosc w zapisie hexadecymalnym)
	battle - 80
	buffed - 1000
	burning - 2
	cannot logout or enter pz - 2000
	drowning - 100
	drunken - 8
	energized - 4
	hasted - 40
	manashield - 10
	paralyzed - 20
	poisoned - 1
	nothing - 0
	

	<CONTAINER STRUCTURE>
	ISOPEN                          0 < 0 = Closed; 1 = Open >
	ICON                            4 < Any item id can be used as icon >
	NAME                            16
	SIZE                            48 < Max size is 36 >
	ITEMS_IN_CONTAINER              56
	ITEM                            60 < Distance between items is 12 >
	ITEM_COUNT                      64 < Distance between items count is 12 >
	CONTAINER_SIZE                  492
	MAX_CONTAINERS                  16


	<VIP STRUCTURE>
	ID                              0
	NAME                            4
	STATUS                          34 < 0 = Offline; 1 = Online >
	ICON                            40 < 1 - 10 >
	VIPSIZE                         44


	<BATTLELIST STRUCYURE>
	ID                              0
	NAME                            4
	X                               36
	Y                               40
	Z                               44
	WALKING                         76 < 0 = Not walking;  1 = Walking >
	DIRECTION                       80 < 0 = North; 1 = East; 2 = South; 3 = West >
	OUTFIT                          96
	HEAD_COLOR                      100
	BODY_COLOR                      104
	LEGS_COLOR                      108
	FEET_COLOR                      112
	ADDON                           116 < 0 = None; 1 = First; 2 = Second; 3 = Both >
	LIGHT                           120
	LIGHT_COLOR                     124
	LIGHT_PATTEN                    127
	HPBAR                           136
	WALK_SPEED                      140
	ISVISIBLE                       144
	SKULL                           148 < 0 = None; 1 = Yellow; 2 = Green; 3 = White; 4 = Red >
	PARTY                           152 < 0 = None; 1 = Leader Invites; 2 = Invited; 3 = Member; 4 = Leader >
	BATTLELIST_SIZE                 160


	<MAP STRUCTURE>
	TILE_SIZE                       172
	MAX_TILE                        2016
	= Tile Struct ==========================
	OBJECTCOUNT                     0
	OBJECTID                        4,  16, 28, 40, 52, 64, 76, 88, 100, 112
	DATA1                           8,  20, 32, 44, 56, 68, 80, 92, 104, 116
	DATA2                           12, 24, 36, 48, 60, 72, 84, 96, 108, 120
	*/

	return 0;
}

