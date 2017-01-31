#ifndef __CONFIG_FILE_HPP
#define __CONFIG_FILE_HPP

#include "file.hpp"
#include <map>
#include <string>
#include <functional>

class ConfigFile{
	BinaryFile file;
	std::map<std::string, std::string> str_cache;
	std::map<std::string, size_t> num_cache;
	void add(std::string name, std::string val);
	void save();
public:
	ConfigFile(std::string path);
	std::string getVal(std::string name, std::string default_val);
	size_t getVal(std::string name, size_t default_val);
	void each(std::function<void(std::string, std::string)> cb);
	
	void setVal(std::string name, std::string val);
	void setVal(std::string name, size_t val);
};

#endif