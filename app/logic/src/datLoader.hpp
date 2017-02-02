#ifndef __DATLOADER_HPP
#define __DATLOADER_HPP

#include "dll.h"
#include <mutex>
#include <vector>

class API DatObject{
	friend class DatLoader;
	friend class Item;
	uint32_t id;
	uint16_t speed;
	uint8_t layer;
	bool ground;
	bool container;
	bool stackable;
	bool used;
	bool usable;
	bool rune;
	bool readable;
	bool writeable;
	uint16_t textSize;
	bool fluidContainer;
	bool splash;
	bool block;
	bool moveable;
	bool blockProjectile;
	bool blockPathFind;
	bool pickupable;
	bool hangable;
	bool horizontal;
	bool vertical;
	bool rotatable;
	uint16_t lightLevel;
	uint16_t lightColor;
	uint16_t offsetX;
	uint16_t offsetY;
	uint16_t change_height;
	bool bottomLayer;
	bool idleAnimated;
	uint16_t mapColor;
	uint16_t lineSpot;
	uint8_t width;
	uint8_t height;
	uint8_t renderSize;
	uint8_t frames;
	uint8_t animatedFrames;
	uint8_t divX;
	uint8_t divY;
	uint8_t divZ;
	std::vector<uint16_t> images;
public:
	DatObject();
	void dump();
	
};

class API DatLoader{
	std::mutex load_state;
	bool loaded;
	std::vector<DatObject*> items;
	std::vector<DatObject*> outfits;
	std::vector<DatObject*> effects;
	std::vector<DatObject*> distances;
	uint32_t signature;
	uint32_t maxItemsId;
	uint32_t maxOutfitsId;
	uint32_t maxEffectsId;
	uint32_t maxDistancesId;
	class BinaryFile* file;
	bool getObject(DatObject& obj, uint32_t id);
public:
	DatObject* getItem(uint32_t id);
	DatObject* getOutfit(uint32_t id);
	DatObject* getEffect(uint32_t id);
	DatObject* getDistance(uint32_t id);
	bool isLoaded();
	DatLoader();
	bool load(std::string path);
	DatObject get(size_t id);
};

#endif