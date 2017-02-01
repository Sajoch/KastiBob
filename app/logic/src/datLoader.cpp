#include "datLoader.hpp"
#include <iostream>

using namespace std;

DatLoader::DatLoader(std::string path):
	file(path)
{
	loaded = false;
	cout<<"dat "<<path<<endl;
	exit(1);
}

bool DatLoader::isLoaded(){
	std::unique_lock<std::mutex> lock(load_state);
	return loaded;
}

DatObject DatLoader::get(size_t id){
	
}