#ifndef __ITEM_HPP
#define __ITEM_HPP

#include <cinttypes>

class Item{
	uint32_t id;
public:
	Item();
	Item(uint32_t _id);
	uint32_t getId();
};

#endif