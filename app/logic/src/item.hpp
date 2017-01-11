#ifndef __ITEM_HPP
#define __ITEM_HPP

#include "thing.hpp"

class Item: public Thing{
	uint32_t id;
public:
	Item(uint32_t _id);
	uint32_t getId();
};

#endif