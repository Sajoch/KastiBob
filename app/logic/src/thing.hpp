#ifndef __THING_HPP
#define __THING_HPP

#include "packet.hpp"

enum class ThingType{NONE, ITEM, CREATURE};

class Thing{
	ThingType type;
	int error;
public:
	Thing();
	Thing(ThingType type);
	static Thing getThing(NetworkPacket& p);
	void setError(int e);
	bool good();
	bool isItem();
	bool isCreature();
};

#endif