#ifndef __LOGINPACKET_HPP
#define __LOGINPACKET_HPP

#include "../packet.hpp"
#include "../cipher.hpp"

class LoginPacket: public NetworkPacket
{
	std::string _login;
	std::string _password;
public:
	LoginPacket(std::string login, std::string password,
		uint16_t tibiaversion, uint16_t ostype, uint32_t dat_signature,
		uint32_t spr_signature, uint32_t pic_signature, RSAcipher& rsa, XTEAcipher& xtea);
};
#endif
