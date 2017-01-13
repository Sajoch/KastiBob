#include <fstream>

class BinaryFile{
  std::fstream file;
  size_t length;
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
};
