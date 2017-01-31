#include "config.hpp"
#include <iostream>

using namespace std;

ConfigFile::ConfigFile(std::string path): file(path){
	std::string name, val;
	uint8_t mode, ch;
	mode = 0;
	while(file.possibleRead(1)){
		ch = file.getUint8();
		//std::cout<<(uint32_t)mode<<": "<<ch<<endl;
		while(true){
			switch(mode){
				case 0: // start line
					if(ch == '#'){
						mode = 4;
						break;
					}else{
						mode = 1;
						name = ch;
						break;
					}
				case 1: // read name
					if(ch != '='){
						name += ch;
						break;
					}else{
						mode = 2;
						break;
					}
				case 2: // start val
					val = ch;
					mode = 3;
					break;
				case 3: // read val
					if(ch != '\r' && ch != '\n'){
						val += ch;
						break;
					}else{
						mode = 4;
						continue;
					}
				case 4: // end line
					if(ch == '\r' || ch == '\n'){
						add(name, val);
						mode = 5;
					}else{
						break;
					}
				case 5: // read to new line
					if(ch != '\r' && ch != '\n'){
						mode = 0;
						continue;
					}
					break;
			}
			break;
		}
	}
	if(mode == 3){
		add(name, val);
	}
}

void ConfigFile::add(std::string name, std::string val){
	//std::cout<<name<<" = "<<val<<std::endl;
	str_cache[name] = val;
	try{
		size_t num = stoul(val);
		num_cache[name] = num;
	}catch(std::invalid_argument e){
		
	}catch(std::out_of_range e){
		
	}
}

void ConfigFile::save(){
	std::map<std::string, std::string>::iterator it;
	std::string str_end = "\r\n";
	file.clear();
	for(it=str_cache.begin();it!=str_cache.end();++it){
		file.write(it->first);
		file.write("=");
		file.write(it->second);
		file.write(str_end);
	}
	file.flush();
}

std::string ConfigFile::getVal(std::string name, std::string default_val){
	std::map<std::string,std::string>::iterator it;
	it = str_cache.find(name);
	if(it != str_cache.end()){
		return it->second;
	}else{
		return default_val;
	}
}
size_t ConfigFile::getVal(std::string name, size_t default_val){
	std::map<std::string,size_t>::iterator it;
	it = num_cache.find(name);
	if(it != num_cache.end()){
		return it->second;
	}else{
		return default_val;
	}
}
void ConfigFile::each(std::function<void(std::string, std::string)> cb){
	std::map<std::string, std::string>::iterator it;
	for(it=str_cache.begin();it!=str_cache.end();++it){
		cb(it->first, it->second);
	}
}

void ConfigFile::setVal(std::string name, std::string val){
	str_cache[name] = val;
	save();
}
void ConfigFile::setVal(std::string name, size_t val){
	str_cache[name] = std::to_string(val);
	num_cache[name] = val;
	save();
}