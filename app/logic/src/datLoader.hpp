#ifndef __DATLOADER_HPP
#define __DATLOADER_HPP

#include "dll.h"
#include "file.hpp"
#include <mutex>
#include <vector>

class API DatObject{
	
};

class API DatLoader{
	std::mutex load_state;
	bool loaded;
	std::vector<DatObject> objects;
	BinaryFile file;
public:
	bool isLoaded();
	DatLoader(std::string path);
	DatObject get(size_t id);
};

#endif