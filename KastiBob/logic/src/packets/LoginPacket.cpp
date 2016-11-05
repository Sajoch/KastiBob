#include "LoginPacket.hpp"

LoginPacket::LoginPacket(std::string login, std::string password,
	uint16_t tibiaversion, uint16_t ostype, RSAcipher& rsa, XTEAcipher& xtea){
		addUint8(1);
		addUint16(ostype);
		addUint16(tibiaversion);
		addUint32(0x467FD7E6);
		addUint32(0x467F9E74);
		addUint32(0x4AE5C3D3);
		size_t rsa_offset = getSize();
		addUint8(0);
		addUint32(xtea.getKey(0));
		addUint32(xtea.getKey(1));
		addUint32(xtea.getKey(2));
		addUint32(xtea.getKey(3));
		addTString(login);
		addTString(password);
		resize(rsa_offset+128);
		rsa.encrypt(&getData()[rsa_offset]);
}
