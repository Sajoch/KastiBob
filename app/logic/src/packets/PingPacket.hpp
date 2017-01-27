#ifndef __PINGPACKET_HPP
#define __PINGPACKET_HPP

#include "../packet.hpp"
#include "../cipher.hpp"

class PingPacket: public NetworkPacket
{
public:
	PingPacket(XTEAcipher* xtea);
};
#endif
