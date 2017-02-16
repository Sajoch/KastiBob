#include "datLoader.hpp"
#include "file.hpp"
#include <iostream>

using namespace std;


DatObject::DatObject(){
	id = 0;
	speed = 0;
	layer = 5;
	ground = false;
	container = false;
	stackable = false;
	used = false;
	usable = false;
	rune = false;
	readable = false;
	writeable = false;
	textSize = 0;
	fluidContainer = false;
	splash = false;
	block = false;
	moveable = false;
	blockProjectile = false;
	blockPathFind = false;
	pickupable = false;
	hangable = false;
	horizontal = false;
	vertical = false;
	rotatable = false;
	lightLevel = 0;
	lightColor = 0;
	offsetX = 0;
	offsetY = 0;
	change_height = 0;
	idleAnimated = false;
	mapColor = 0;
	lineSpot = 0;
	width = 1;
	height = 1;
	renderSize = 32;
	blendFrames = 0;
	animatedFrames = 1;
	divX = 1;
	divY = 1;
	divZ = 0;
}

void DatObject::dump(){
	cout<<"id "<<id<<endl;
	cout<<"speed = "<<speed<<endl;
	cout<<"layer = "<<layer<<endl;
	cout<<"ground = "<<(ground?"true":"false")<<endl;
	cout<<"container = "<<(container?"true":"false")<<endl;
	cout<<"stackable = "<<(stackable?"true":"false")<<endl;
	cout<<"used = "<<(used?"true":"false")<<endl;
	cout<<"usable = "<<(usable?"true":"false")<<endl;
	cout<<"rune = "<<(rune?"true":"false")<<endl;
	cout<<"readable = "<<(readable?"true":"false")<<endl;
	cout<<"writeable = "<<(writeable?"true":"false")<<endl;
	cout<<"textSize = "<<textSize<<endl;
	cout<<"fluidContainer = "<<(fluidContainer?"true":"false")<<endl;
	cout<<"splash = "<<(splash?"true":"false")<<endl;
	cout<<"block = "<<(block?"true":"false")<<endl;
	cout<<"moveable = "<<(moveable?"true":"false")<<endl;
	cout<<"blockProjectile = "<<(blockProjectile?"true":"false")<<endl;
	cout<<"blockPathFind = "<<(blockPathFind?"true":"false")<<endl;
	cout<<"pickupable = "<<(pickupable?"true":"false")<<endl;
	cout<<"hangable = "<<(hangable?"true":"false")<<endl;
	cout<<"horizontal = "<<(horizontal?"true":"false")<<endl;
	cout<<"vertical = "<<(vertical?"true":"false")<<endl;
	cout<<"rotatable = "<<(rotatable?"true":"false")<<endl;
	cout<<"lightLevel = "<<lightLevel<<endl;
	cout<<"lightColor = "<<lightColor<<endl;
	cout<<"offsetX = "<<offsetX<<endl;
	cout<<"offsetY = "<<offsetY<<endl;
	cout<<"change_height = "<<change_height<<endl;
	cout<<"bottomLayer = "<<(bottomLayer?"true":"false")<<endl;
	cout<<"idleAnimated = "<<(idleAnimated?"true":"false")<<endl;
	cout<<"mapColor = "<<mapColor<<endl;
	cout<<"lineSpot = "<<lineSpot<<endl;
	cout<<"width = "<<(uint32_t)width<<endl;
	cout<<"height = "<<(uint32_t)height<<endl;
	cout<<"renderSize = "<<(uint32_t)renderSize<<endl;
	cout<<"frames = "<<(uint32_t)blendFrames<<endl;
	cout<<"animatedFrames = "<<(uint32_t)animatedFrames<<endl;
	cout<<"divX = "<<(uint32_t)divX<<endl;
	cout<<"divY = "<<(uint32_t)divY<<endl;
	cout<<"divZ = "<<(uint32_t)divZ<<endl;
	cout<<"images = ";
	for(uint32_t i=0;i<images.size();i++){
		cout<<images[i]<<", ";
	}
	cout<<endl;
	
}

uint32_t DatObject::getId(){
	return id;
}
uint32_t DatObject::getBlend(){
	return blendFrames;
}

DatLoader::DatLoader(std::string path){
	_path = path;
	loaded = false;
}

bool DatLoader::load(){
	file = new BinaryFile(_path);
	if(!file->possibleRead(12)){
		delete file;
		file = 0;
		return false;
	}
	signature = file->getUint32();
	maxItemsId = file->getUint16();
	maxOutfitsId = file->getUint16();
	maxEffectsId = file->getUint16();
	maxDistancesId = file->getUint16();
	uint8_t mode;
	uint32_t max, offset, id;
	mode = 0;
	std::vector<DatObject*>* array;
	while(mode<4){
		switch(mode){
			case 0: //items
				array = &items;
				max = maxItemsId - 100;
				offset = 100;
				break;
			case 1: //outfits
				array = &outfits;
				max = maxOutfitsId;
				offset = 0;
				break;
			case 2: //effects
				array = &effects;
				max = maxEffectsId;
				offset = 0;
				break;
			case 3: //distances
				array = &distances;
				max = maxDistancesId;
				offset = 0;
				break;
		}
		for(uint16_t i=0;i<max;i++){
			DatObject* obj = new DatObject();
			id = offset + i;
			//cout<<"mode "<<mode<<" id "<<id<<endl;
			if(getObject(*obj, id)){
				array->push_back(obj);
			}else{
				delete file;
				file = 0;
				return false;
			}
		}
		mode++;
	}
	
	load_state.lock();
	loaded = true;
	load_state.unlock();
	delete file;
	return true;
}

bool DatLoader::getObject(DatObject& obj, uint32_t id){
	obj.id = id;
	uint8_t attr;
	bool force = false;
	//cout<<"object "<<id<<endl;
	//loop when can read byte and it is not 0xff
	while(file->possibleRead(1) && (attr = file->getUint8())!=0xff && !force){
		//cout<<(void*)(uint32_t)attr<<" object attribute"<<endl;
		switch(attr){
			case 0x00:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.speed = file->getUint16();
				obj.ground = true;
				obj.layer = 0;
				break;
			case 0x01:
				obj.layer = 1;
				break;
			case 0x02:
				obj.layer = 2;
				break;
			case 0x03:
				obj.layer = 3;
				break;
			case 0x04:
				obj.container = true;
				break;
			case 0x05:
				obj.stackable = true;
				break;
			case 0x06:
				obj.used = true;
				break;
			case 0x07:
				obj.usable = true;
				break;
			case 0x08:
				obj.rune = true;
				break;
			case 0x09:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.readable = true;
				obj.writeable = true;
				obj.textSize = file->getUint16();
				break;
			case 0x0a:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.readable = true;
				obj.textSize = file->getUint16();
				break;
			case 0x0b:
				obj.fluidContainer = true;
				break;
			case 0x0c:
				obj.splash = true;
				break;
			case 0x0d:
				obj.block = true;
				break;
			case 0x0e:
				obj.moveable = false;
				break;
			case 0x0f:
				obj.blockProjectile = true;
				break;
			case 0x10:
				obj.blockPathFind = true;
				break;
			case 0x11:
				obj.pickupable = true;
				break;
			case 0x12:
				obj.hangable = true;
				break;
			case 0x13:
				obj.horizontal = true;
				break;
			case 0x14:
				obj.vertical = true;
				break;
			case 0x15:
				obj.rotatable = true;
				break;
			case 0x16:
				if(!file->possibleRead(4)){
					force = true;
					break;
				}
				obj.lightLevel = file->getUint16();
				obj.lightColor = file->getUint16();
				break;
			case 0x17:
				//cout<<"0x17 object attribute"<<endl;
				break;
			case 0x18:
				//cout<<"0x19 object attribute"<<endl;
				break;
			case 0x19:
				if(!file->possibleRead(4)){
					force = true;
					break;
				}
				obj.offsetX = file->getUint16();
				obj.offsetY = file->getUint16();
				break;
			case 0x1a:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.change_height = file->getUint16();
				break;
			case 0x1b:
				obj.bottomLayer = true;
				break;
			case 0x1c:
				obj.idleAnimated = true;
				break;
			case 0x1d:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.mapColor = file->getUint16();
				break;
			case 0x1e:
				if(!file->possibleRead(2)){
					force = true;
					break;
				}
				obj.lineSpot = file->getUint16();
				break;
			case 0x1f:
				//cout<<"0x1f object attribute"<<endl;
				break;
			case 0x20:
				//cout<<"0x20 object attribute - lookThrough"<<endl;
				break;
			default:
				obj.dump();
				cout<<"exit "<<(void*)(uint32_t)attr<<" object attribute"<<endl;
				exit(1);
				break;
		}
	}
	if(force){
		cout<<"force"<<endl;
		exit(1);
		return false;
	}
	obj.width = file->getUint8();
	obj.height = file->getUint8();
	if(obj.width == 0 || obj.height == 0){
		cout<<"dat object has 0 area"<<endl;
		return false;
	}
	if(obj.width > 1 || obj.height > 1){
		obj.renderSize = file->getUint8();
		//cout<<"rederSize for id "<<obj.id<<" is "<<obj.renderSize<<endl;
	}
	obj.blendFrames = file->getUint8();
	obj.divX = file->getUint8();
	obj.divY = file->getUint8();
	obj.divZ = file->getUint8();
	obj.animatedFrames = file->getUint8();
	uint64_t sprites = obj.width * obj.height * obj.blendFrames
										 * obj.divX * obj.divY * obj.animatedFrames * obj.divZ;
	
	if(!file->possibleRead(sprites)){
		cout<<"force possibleRead"<<endl;
		exit(1);
		return false;
	}
	for(uint64_t ii=0;ii<sprites; ii++){
		obj.images.push_back(file->getUint16());
	}
	return true;
}

bool DatLoader::isLoaded(){
	std::unique_lock<std::mutex> lock(load_state);
	return loaded;
}

DatObject* DatLoader::getItem(uint32_t id){
	if(id < 100){
		return 0;
	}
	id -= 100;
	if(id>items.size()){
		return 0;
	}
	return items[id];
}
DatObject* DatLoader::getOutfit(uint32_t id){
	if(id>outfits.size()){
		return 0;
	}
	return outfits[id];
}
DatObject* DatLoader::getEffect(uint32_t id){
	if(id>effects.size()){
		return 0;
	}
	return effects[id];
}
DatObject* DatLoader::getDistance(uint32_t id){
	if(id>distances.size()){
		return 0;
	}
	return distances[id];
}
DatObject DatLoader::get(size_t id){
	
}
std::string DatLoader::getPath(){
	return _path;
}