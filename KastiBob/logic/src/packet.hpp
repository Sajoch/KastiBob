#ifndef __PACKET_HPP
#define __PACKET_HPP

#include <string>
#include <cinttypes>

class NetworkPacket {
	friend class NetworkManager;
	std::string buffer;
public:
	NetworkPacket();
	void addUint8(uint8_t a);
	void addUint16(uint16_t a);
	void addUint32(uint32_t a);
	void addString(std::string a);
	void addTString(std::string a);
	uint32_t checksum();
	void add_header();

	uint8_t getUint8();
	uint16_t getUint16();
	uint32_t getUint32();
	std::string getTString();

	std::string& getData();
	size_t getSize();
	void resize(size_t len);
};
#endif
