#include "spriteLoader.hpp"

#include <iostream>

using namespace std;

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
  size_t id = 0;
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

std::string SpriteLoader::getError(){
  return error;
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
  std::string buffer(sp.size, '\0');
  spr.goToOffset(sp.offset+5);
  spr.readBuffer(buffer);
  size_t offset_read = 0;
  uint32_t pixelOffset = 0;
  sp.image.resize(4*32*32, '\0');
  size_t data_left = buffer.size();
  uint32_t blank, datas;
  while(data_left>0){
    if(data_left<4){
      error = "cannot read header of sprite ";
      return "";
    }
    blank = (uint8_t)buffer[offset_read + 1];
    blank <<= 8;
    blank |= (uint8_t)buffer[offset_read];
    pixelOffset += blank * 4;
    offset_read += 2;
    if(blank > 3076){
      error = "too much blank pixels";
      return "";
    }
    datas = (uint8_t)buffer[offset_read + 1];
    datas <<= 8;
    datas |= (uint8_t)buffer[offset_read];
    offset_read += 2;
    if(datas > 3076){
      error = "too much data pixels";
      return "";
    }
    data_left -= 4;
    if(data_left < (3*datas)){
      error = "not enough pixel data";
      return "";
    }
    for(uint16_t ip=0;ip<datas;ip++){
      sp.image[pixelOffset+0] = buffer[offset_read];
      sp.image[pixelOffset+1] = buffer[offset_read + 1];
      sp.image[pixelOffset+2] = buffer[offset_read + 2];
      sp.image[pixelOffset+3] = 255;
      pixelOffset += 4;
      offset_read += 3;
    }
    data_left -= datas * 3;
  }
  sp.loaded = true;
  std::string outPath="i";
  outPath += to_string(id);
  outPath += ".raw";
  fstream out(outPath, ios::binary|ios::trunc|ios::out);
  cout<<"out "<<outPath<<" is "<<(out.good()?"true":"false")<<endl;
  out.write(sp.image.data(), sp.image.size());
  return sp.getImage();
}
