#ifndef __BINARY_FILE_HPP
#define __BINARY_FILE_HPP

#include <fstream>

class BinaryFile{
  std::fstream file;
  size_t length;
  std::string path;
public:
  BinaryFile(std::string name);
  bool possibleRead(size_t a);
  uint32_t getUint32();
  uint16_t getUint16();
  uint8_t getUint8();
  void goToOffset(size_t a);
  bool readBuffer(std::string& buf);

  size_t getOffset();
  void readRest(std::string& buf);
  
  void write(std::string val);
  void clear();
  void flush();
};

#endif