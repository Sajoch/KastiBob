#include "file.hpp"

using namespace std;

BinaryFile::BinaryFile(std::string name):
file(name.c_str(), ios::in|ios::binary)
{
  file.seekg (0, file.end);
  length = file.tellg();
  file.seekg (0, file.beg);
}
bool BinaryFile::possibleRead(size_t a){
  size_t offset = file.tellg();
  offset+=a;
  if(offset<=length){
    return true;
  }
  return false;
}

uint32_t BinaryFile::getUint32(){
  uint32_t ret;
  uint8_t buf[4];
  file.read((char*)buf, 4);
	ret =  (buf[3]&0xff);
	ret <<= 8;
	ret |= (buf[2]&0xff);
	ret <<= 8;
	ret |= (buf[1]&0xff);
	ret <<= 8;
	ret |= (buf[0]&0xff);
	return ret;
}

uint16_t BinaryFile::getUint16(){
  uint16_t ret;
  uint8_t buf[2];
  file.read((char*)buf, 2);
	ret  = (buf[1]&0xff);
	ret <<= 8;
	ret |= (buf[0]&0xff);
	return ret;
}

uint8_t BinaryFile::getUint8(){
  uint8_t ret;
  file.read((char*)&ret, 1);
	return ret;
}

void BinaryFile::goToOffset(size_t a){
  file.seekg(a, file.beg);
}
