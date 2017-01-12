#include <vector>
#include <string>
#include "file.hpp"

using namespace std;

class Sprite{
  friend class SpriteLoader;
  bool loaded;
  size_t offset;
  uint32_t size;
  std::string image;
public:
  Sprite(uint32_t off);
  std::string getImage();
};


class SpriteLoader{
  std::string error;
  std::vector<Sprite> sprites;
  BinaryFile spr;
public:
  std::string getError();
  SpriteLoader(std::string path);
  std::string getImage(uint32_t id);
};
