#include <vector>
#include <string>
#include <fstream>
#include "configoption.hpp"

class Config{
	std::string path;
	std::vector<ConfigOption> options;
public:
	Config();
	Config(std::string _path);
	bool load();
	bool save();
	
	ConfigOption& operator[](std::string name){
		return getOption(name);
	}
	ConfigOption& getOption(std::string name);
};