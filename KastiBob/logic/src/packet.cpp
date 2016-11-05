#include "packet.hpp"

NetworkPacket::NetworkPacket(){}
void NetworkPacket::addUint8(uint8_t a){
	buffer.push_back(a);
}
void NetworkPacket::addUint16(uint16_t a){
	buffer.push_back(a&0xff);
	buffer.push_back((a>>8)&0xff);
}
void NetworkPacket::addUint32(uint32_t a){
	buffer.push_back((a)&0xff);
	buffer.push_back((a>>8)&0xff);
	buffer.push_back((a>>16)&0xff);
	buffer.push_back((a>>24)&0xff);
}
void NetworkPacket::addString(std::string a){
	for(size_t i=0;i<a.size();i++)
		buffer.push_back(a[i]);
}
void NetworkPacket::addTString(std::string a){
	addUint16(a.size());
	addString(a);
}
uint32_t NetworkPacket::checksum(){
	const uint16_t MOD_ADLER=65521;
	size_t tlen;
	uint8_t* data = (uint8_t*)buffer.data();
	size_t len = buffer.size();
	uint32_t a = 1, b = 0;
	while (len > 0){
			tlen = len > 5552 ? 5552 : len;
			len -= tlen;
			do{
					a += *data++;
					b += a;
			} while (--tlen);
			a %= MOD_ADLER;
			b %= MOD_ADLER;
	}
	return (b << 16) | a;
}
void NetworkPacket::add_header(){
	uint32_t crc = checksum();
	buffer.insert(0, (char*)&crc, 4);
	uint16_t len = buffer.size();
	buffer.insert(0, (char*)&len, 2);
}

uint8_t NetworkPacket::getUint8() {
	uint8_t a = buffer[0];
	buffer.erase(buffer.begin());
	return a;
}
uint16_t NetworkPacket::getUint16() {
	uint16_t a = ((buffer[1] >> 8) & 0xff00) | (buffer[0] & 0xff);
	buffer.erase(buffer.begin(), buffer.begin()+2);
	return a;
}
uint32_t NetworkPacket::getUint32() {
	uint16_t a = ((buffer[3] >> 24) & 0xff000000) | ((buffer[2] >> 16) & 0xff0000) |
							 ((buffer[1] >> 8) & 0xff00) | (buffer[0] & 0xff);
	buffer.erase(buffer.begin(), buffer.begin()+4);
	return a;
}

std::string NetworkPacket::getTString() {
	uint16_t len = getUint16();
	std::string ret(&buffer[0], len);
	buffer.erase(buffer.begin(), buffer.begin() + len);
	return ret;
}

std::string& NetworkPacket::getData(){
	return buffer;
}
size_t NetworkPacket::getSize() {
	return buffer.size();
}
void NetworkPacket::resize(size_t len) {
	return buffer.resize(len);
}
