#include "MovePacket.hpp"

MovePacket::MovePacket(ClientDirectory dir, XTEAcipher& xtea){
	addUint16(1);
	switch(dir){
		case ClientDirectory::NORTH:
			addUint8(0x65);
		break;
		case ClientDirectory::EAST:
			addUint8(0x66);
		break;
		case ClientDirectory::SOUTH:
			addUint8(0x67);
		break;
		case ClientDirectory::WEST:
			addUint8(0x68);
		break;
		case ClientDirectory::NE:
			addUint8(0x6A);
		break;
		case ClientDirectory::SE:
			addUint8(0x6B);
		break;
		case ClientDirectory::SW:
			addUint8(0x6C);
		break;
		case ClientDirectory::NW:
			addUint8(0x6D);
		break;
	}
	xteaEncrypt(xtea);
}