#ifndef __ONEBYTEPACKET_HPP
#define __ONEBYTEPACKET_HPP

#include "../packet.hpp"
#include "../cipher.hpp"

class OneBytePacket: public NetworkPacket
{
public:
	OneBytePacket(uint8_t val, XTEAcipher& xtea);
};
#endif
