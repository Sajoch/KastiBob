#include "spriteLoader.hpp"

Sprite::Sprite(uint32_t off){
  offset = off;
  loaded = false;
  size = 0;
}

std::string Sprite::getImage(){
  return image;
}

SpriteLoader::SpriteLoader(std::string path):
spr(path)
{
  if(!spr.possibleRead(4)){
    error = "cannot read signature";
    return;
  }
  spr.getUint32();
  if(!spr.possibleRead(2)){
    error = "cannot read spriteCount";
    return;
  }
  uint32_t spriteCount = spr.getUint16();
  for(uint32_t id=0;id<spriteCount;id++){
    if(!spr.possibleRead(4)){
      error = "cannot read offset of header of sprite";
      return;
    }
    Sprite sp(spr.getUint32());
    sprites.push_back(sp);
  }
  for(vector<Sprite>::iterator it=sprites.begin();it!=sprites.end();++it){
    if((*it).offset == 0)
      continue;
    (*it).loaded = false;
    spr.goToOffset((*it).offset);
    if(!spr.possibleRead(5)){
      error = "cannot read header of sprite";
      return;
    }
    spr.getUint8();
    spr.getUint8();
    spr.getUint8();
    (*it).size = spr.getUint16();
    if((*it).size > 3444){
      error = "has too big size";
      return;
    }
  }
}

std::string SpriteLoader::getImage(uint32_t id){
  if(id>=sprites.size()){
    error = "id too grater than sprites size";
    return "";
  }
  Sprite& sp = sprites[id];
  if(sp.loaded){
    return sp.getImage();
  }
  size_t offset_read = 0;
  uint32_t pixelOffset = 0;
  sp.image.resize(3*32*32, '\0');
  while(offset_read < sp.size){
    if(!spr.possibleRead(4)){
      error = "cannot read header of sprite ";
      return "";
    }
    uint32_t pixelscount = spr.getUint16();
    pixelOffset += pixelscount*3;
    offset_read += 2;
    if(pixelscount > 3076){
      error = "has too big pixel transparent chunk";
      return "";
    }
    pixelscount = spr.getUint16();
    offset_read += 2;
    if(pixelscount > 3076){
      error = "has too big pixel chunk";
      return "";
    }
    uint8_t rgb[3];
    if(!spr.possibleRead(3*pixelscount)){
      error = "cannot read rgb of sprite";
      return "";
    }
    for(uint16_t ip=0;ip<pixelscount;ip++){
      rgb[0] = spr.getUint8();
      rgb[1] = spr.getUint8();
      rgb[2] = spr.getUint8();
      sp.image[pixelOffset+0] = rgb[0];
      sp.image[pixelOffset+1] = rgb[1];
      sp.image[pixelOffset+2] = rgb[2];
      pixelOffset++;
      offset_read += 3;
    }
  }
  sp.loaded = true;
  return sp.getImage();
}
