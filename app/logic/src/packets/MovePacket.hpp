#ifndef __MOVEPACKET_HPP
#define __MOVEPACKET_HPP

#include "../packet.hpp"
#include "../cipher.hpp"
#include "../utils.hpp"

class MovePacket: public NetworkPacket
{
public:
	MovePacket(ClientDirectory dir, XTEAcipher& xtea);
};
#endif
