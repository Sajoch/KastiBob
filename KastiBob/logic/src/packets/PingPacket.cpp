#include "PingPacket.hpp"

PingPacket::PingPacket(XTEAcipher& xtea){
	addUint16(1);
	addUint8(0x1e);
	xteaEncrypt(xtea);
}