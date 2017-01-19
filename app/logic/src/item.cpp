#include "item.hpp"

Item::Item(uint32_t _id):
	Thing(ThingType::ITEM), id(_id)
{
	setError(0);
}