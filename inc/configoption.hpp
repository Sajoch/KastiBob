#include <string>
#include <cinttypes>

class ConfigOption{
	friend class Config;
	static uint8_t decodeChar;
	std::string name;
	bool disable;
	std::string line;
	std::string svalue;
	uint32_t ivalue;
	bool validInt;
	ConfigOption(std::string _line);
	bool isWhitechar(char c);
	bool getIntFromString(uint32_t& r, std::string s);
	void setStringFromInt(std::string& r, uint32_t s);
	void xorString(std::string& r);
	std::string getLine();
public:
	std::string getName();
	std::string getString();
	std::string getDecodeString();
	uint32_t getDecodeInt();
	uint32_t getInt();
	void setInt(uint32_t v);
	void setString(std::string v);
	void encodeValue();
};