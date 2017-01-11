#ifndef __THING_HPP
#define __THING_HPP

#include "packet.hpp"

class Thing{
	int error;
public:
	Thing();
	Thing(NetworkPacket& p);
	bool good();
};

#endif