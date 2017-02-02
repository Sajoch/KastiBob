#include <vector>
#include <string>
#include "dll.h"
#include "file.hpp"

using namespace std;

class API Sprite{
  friend class SpriteLoader;
  bool loaded;
  size_t offset;
  uint32_t size;
  std::string image;
  bool RawToPng();
public:
  void toBase64();
  Sprite(uint32_t off);
  std::string getImage();
};


class API SpriteLoader{
  std::string error;
  std::vector<Sprite> sprites;
  std::string buffer;
  size_t offset_to_data;
public:
  std::string getError();
  SpriteLoader(std::string path);
  std::string getImage(uint32_t id);
};
