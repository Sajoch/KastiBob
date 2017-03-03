#include "config.hpp"
#include <iostream>

using namespace std;

Config::Config(){
	
}
Config::Config(std::string _path):
	path(_path)
{
	
}
bool Config::load(){
	std::fstream file;
	file.open(path, std::ios::in|std::ios::out);
	if(!file.good()){
		file.open(path, std::ios::out);
	}
	if(!file.good()){
		std::cout<<"no access to "<<path<<std::endl;
		return false;
	}
	while(file.good()){
		std::string line;
		std::getline(file, line);
		ConfigOption oline(line);
		options.push_back(oline);
	}
	return true;
}

ConfigOption& Config::getOption(std::string name){
	std::vector<ConfigOption>::iterator it;
	for(it = options.begin();it != options.end();++it){
		ConfigOption& o = (*it);
		if(o.getName() == name){
			return o;
		}
	}
	options.push_back(ConfigOption(""));
	ConfigOption& o = options.back();
	o.name = name;
	return o;
}
bool Config::save(){
	std::fstream file;
	file.open(path, std::ios::out|std::ios::trunc);
	if(!file.good()){
		return false;
	}
	std::vector<ConfigOption>::iterator it;
	for(it = options.begin();it != options.end();++it){
		ConfigOption& o = (*it);
		file<<o.getLine()<<endl;
	}
	file.close();
	return true;
}