#include "packet.hpp"
#include <iostream>
NetworkPacket::NetworkPacket(){}

void NetworkPacket::addUint32(std::string& b, uint32_t v){
	b.push_back((v)&0xff);
	b.push_back((v>>8)&0xff);
	b.push_back((v>>16)&0xff);
	b.push_back((v>>24)&0xff);
}

uint8_t NetworkPacket::peekUint8(std::string& b){
	uint8_t ret;
	ret = (b[0]&0xff);
	return ret;
}
uint16_t NetworkPacket::peekUint16(std::string& b){
	uint16_t ret;
	ret = (b[1]&0xff);
	ret<<=8;
	ret |= (b[0]&0xff);
	return ret;
}
uint32_t NetworkPacket::peekUint32(std::string& b){
	uint32_t ret;
	ret =  (b[3]&0xff);
	ret <<= 8;
	ret |= (b[2]&0xff);
	ret <<= 8;
	ret |= (b[1]&0xff);
	ret <<= 8;
	ret |= (b[0]&0xff);
	return ret;
}
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
	uint8_t a = peekUint8(buffer);
	buffer.erase(buffer.begin());
	return a;
}
uint16_t NetworkPacket::getUint16() {
	uint16_t a = peekUint16(buffer);
	buffer.erase(buffer.begin(), buffer.begin()+2);
	return a;
}
uint32_t NetworkPacket::getUint32() {
	uint32_t a = peekUint32(buffer);
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
void NetworkPacket::xteaDecrypt(XTEAcipher& xtea){
	xtea.decrypt(buffer);
}
void NetworkPacket::xteaEncrypt(XTEAcipher& xtea){
	buffer.append((8-(buffer.size()%8)), 0xAC);
	xtea.encrypt(buffer);
}

void NetworkPacket::dump(){
	static const char hex[] = "0123456789abcdef";
	for(size_t i=0;i<buffer.size();i++){
		uint8_t byte = buffer[i];
		std::cout<<"0x"<<hex[(byte>>4)&0xf]<<hex[byte&0xf]<<" ";
	}
	std::cout<<std::endl<<"==================="<<std::endl;
}