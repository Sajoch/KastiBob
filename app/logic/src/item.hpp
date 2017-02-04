#ifndef __ITEM_HPP
#define __ITEM_HPP

#include <cinttypes>
#include "dll.h"

class API Item{
	friend class Square;
	uint32_t id;
	class DatObject* itemTemplate;
	uint16_t stack;
public:
	Item();
	Item(uint32_t _id, class DatLoader* dat, class NetworkPacket& p, class Client* c);
	uint32_t getId();
};

#endif