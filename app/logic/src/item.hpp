#ifndef __ITEM_HPP
#define __ITEM_HPP

#include <cinttypes>
#include "dll.h"

class API Item{
	friend class Square;
	int32_t id;
	class DatObject* itemTemplate;
	uint16_t stack;
public:
	Item();
	Item(int32_t _id, class DatLoader* dat, class NetworkPacket& p, class Client* c);
	int32_t getId();
	class DatObject* getTemplate();
};

#endif