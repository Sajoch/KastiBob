#include "MovePacket.hpp"

MovePacket::MovePacket(ClientDirectory dir, XTEAcipher& xtea){
	addUint16(1);
	switch(dir){
		case ClientDirectory::STOP:
			addUint8(0xBC);
		break;
		
		case ClientDirectory::LOOK_NORTH:
			addUint8(0x6D);
		break;
		case ClientDirectory::LOOK_EAST:
			addUint8(0x72);
		break;
		case ClientDirectory::LOOK_SOUTH:
			addUint8(0x73);
		break;
		case ClientDirectory::LOOK_WEST:
			addUint8(0x70);
		break;
		
		case ClientDirectory::NORTH:
			addUint8(0x67);
		break;
		case ClientDirectory::EAST:
			addUint8(0x64);
		break;
		case ClientDirectory::SOUTH:
			addUint8(0x65);
		break;
		case ClientDirectory::WEST:
			addUint8(0x6A);
		break;
		case ClientDirectory::NE:
			addUint8(0x69);
		break;
		case ClientDirectory::SE:
			addUint8(0x6B);
		break;
		case ClientDirectory::SW:
			addUint8(0x6E);
		break;
		case ClientDirectory::NW:
			addUint8(0x6F);
		break;
	}
	xteaEncrypt(xtea);
}