#include "configoption.hpp"


uint8_t ConfigOption::decodeChar = 0x6a;

bool ConfigOption::isWhitechar(char c){
	if(c==' ' || c=='\t'){
		return true;
	}
	return false;
}

bool ConfigOption::getIntFromString(uint32_t& r, std::string s){
	size_t l = s.size();
	if(l < 1){
		return false;
	}
	r = 0;
	uint32_t podstawa = 1;
	for(size_t i=1;i<l;i++){
		podstawa*=10;
	}
	if(podstawa != 1 && podstawa%10!=0){
		return false;
	}
	for(size_t i=0;i<l;i++){
		char c = s[i];
		if(c>='0' && c<='9'){
			uint32_t t = c - '0';
			r+=t * podstawa;
			podstawa /= 10;
		}else{
			return false;
		}
	}
	return true;
}

void ConfigOption::setStringFromInt(std::string& r, uint32_t s){
	r.clear();
	const char nums[] ="0123456789";
	if(s==0){
		r = "0";
	}
	while(s>0){
		r=nums[s%10]+r;
		s/=10;
	}
}

ConfigOption::ConfigOption(std::string _line){
	//cout<<nline<<": "<<_line<<endl;
	line = _line;
	size_t l=_line.size();
	if(l<1){
		disable = true;
	}else{
		disable = false;
	}
	ivalue = 0;
	validInt = false;
	int state = 0;
	for(size_t i=0;i<l;i++){
		char c = _line[i];
		switch(state){
			case 0: //skip whitechars
				if(isWhitechar(c)){
					continue;
				}else{
					state++;
				}
			case 1: //check is disabled
				state++;
				if(c=='#'){
					disable = true;
					break;
				}
			case 2: //read name
				if(c!='=' && c!=' ' && c!='\t'){
					name+=c;
					break;
				}else{
					state++;
				}
			case 3: //skip whitechars
				if(isWhitechar(c)){
					continue;
				}else{
					state++;
				}
			case 4: //skip equal
				if(c=='='){
					continue;
				}else{
					state++;
				}
			case 5: //skip whitechars
				if(isWhitechar(c)){
					continue;
				}else{
					state++;
				}
			case 6://read value
				svalue+=c;
			break;
		}
	}
	if(getIntFromString(ivalue, svalue)){
		validInt = true;
	}else{
		validInt = false;
	}
	//cout<<"name "<<name<<endl;
	//cout<<"svalue "<<svalue<<endl;
	//if(validInt){
	//	cout<<"ivalue "<<ivalue<<endl;
	//}
	//cout<<"disabled "<<(disable?"true":"false")<<endl;
}


std::string ConfigOption::getName(){
	if(!disable){
		return name;
	}
	return "";
}
std::string ConfigOption::getString(){
	return svalue;
}
std::string ConfigOption::getDecodeString(){
	std::string nbuffer = svalue;
	if(nbuffer.size()%8 != 0){
		return "";
	}
	xorString(nbuffer);
	size_t l = nbuffer.size();
	for(size_t i=l-8;i<l;i++){
		if(nbuffer[i]==0){
			nbuffer.resize(i);
			break;
		}
	}
	return nbuffer;
}
uint32_t ConfigOption::getDecodeInt(){
	uint32_t ret;
	std::string nbuffer = getDecodeString();
	if(getIntFromString(ret, nbuffer)){
		return ret;
	}else{
		return 0;
	}
}
uint32_t ConfigOption::getInt(){
	if(validInt){
		return ivalue;
	}
	return 0;
}
void ConfigOption::setInt(uint32_t v){
	ivalue = v;
	validInt = true;
	setStringFromInt(svalue, ivalue);
	line.clear();
}
void ConfigOption::setString(std::string v){
	svalue = v;
	line.clear();
}
void ConfigOption::xorString(std::string& r){
	size_t psize = r.size();
	uint8_t odc = decodeChar;
	for(size_t i=0;i<psize;i++){
		if(odc > 127){
			odc = decodeChar;
		}
		r[i] = r[i] ^ odc;
		odc++;
	}
}
void ConfigOption::encodeValue(){
	size_t psize = svalue.size();
	psize += 8 - (psize % 8);
	std::string nbuffer;
	nbuffer.insert(0, svalue);
	nbuffer.resize(psize);
	xorString(nbuffer);
	svalue = nbuffer;
	validInt = false;
}

std::string ConfigOption::getLine(){
	if(!line.empty()){
		return line;
	}
	if(name.empty()){
		return "";
	}
	return name+"="+svalue;
}