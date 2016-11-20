#include "LoginPacket.hpp"

LoginPacket::LoginPacket(std::string login, std::string password,
	uint16_t tibiaversion, uint16_t ostype, uint32_t dat_signature,
	uint32_t spr_signature, uint32_t pic_signature, RSAcipher& rsa, XTEAcipher& xtea){
		addUint8(1);
		addUint16(ostype);
		addUint16(tibiaversion);
		addUint32(dat_signature);
		addUint32(spr_signature);
		addUint32(pic_signature);
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
LoginPacket::LoginPacket(std::string login, std::string password,
	uint16_t tibiaversion, uint16_t ostype, uint32_t dat_signature,
	uint32_t spr_signature, uint32_t pic_signature, 
	uint32_t data[5], std::string name,
	RSAcipher& rsa, XTEAcipher& xtea){
		addUint8(0x0A);
		addUint16(ostype);
		addUint16(tibiaversion);
		size_t rsa_offset = getSize();
		addUint8(0);
		addUint32(xtea.getKey(0));
		addUint32(xtea.getKey(1));
		addUint32(xtea.getKey(2));
		addUint32(xtea.getKey(3));
		addUint8(0);
		addTString(name);
		addTString(login);
		addTString(password);
		for(int i=0;i<5;i++){
			addUint8(data[i]);
		}
		resize(rsa_offset+128);
		rsa.encrypt(&getData()[rsa_offset]);
}
