#include "OneBytePacket.hpp"

OneBytePacket::OneBytePacket(uint8_t val, XTEAcipher& xtea){
	addUint16(1);
	addUint8(val);
	xteaEncrypt(xtea);
}