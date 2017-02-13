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
  std::string raw;
  bool RawToPng();
public:
  void toBase64();
  Sprite();
  Sprite(uint32_t off);
  void clearPng();
  void clearRaw();
  std::string getImage();
  std::string getRaw();
  std::string* getRawPointer();
};


class API SpriteLoader{
  std::string error;
  std::vector<Sprite> sprites;
  Sprite empty;
  std::string buffer;
  size_t offset_to_data;
  class BinaryFile* spr;
public:
  std::string getError();
  SpriteLoader(std::string path);
  ~SpriteLoader();
  bool load();
  bool loadRaw(Sprite& sp);
  void clearPng(uint32_t id);
  void clearRaw(uint32_t id);
  std::string getImage(uint32_t id);
  Sprite& get(uint32_t id);
};
