#include "PingPacket.hpp"

PingPacket::PingPacket(XTEAcipher* xtea){
	addUint16(1);
	addUint8(0x1C);
	xteaEncrypt(xtea);
}