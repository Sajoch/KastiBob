//read sprites and convert to base64 png
#include "spriteLoader.hpp"
#include <png.h>

using namespace std;

Sprite::Sprite(uint32_t off){
  offset = off;
  loaded = false;
  size = 0;
}

std::string Sprite::getImage(){
  return image;
}

bool Sprite::RawToPng(){
  png_structp p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(p == NULL){
    return false;
  }
  png_infop info_ptr = png_create_info_struct(p);
  if(p == NULL){
    png_destroy_write_struct(&p, NULL);
    return false;
  }
  if(setjmp(png_jmpbuf(p)) != 0){
    png_destroy_write_struct(&p, &info_ptr);
    return false;
  }
  png_set_IHDR(p, info_ptr, 32, 32, 8, PNG_COLOR_TYPE_RGB_ALPHA,
            PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);
  string png_buffer;
  unsigned char* img_p = (unsigned char*)image.data();
  unsigned char* img_rows[32];
  for(int i=0;i<32;i++){
    img_rows[i] = &img_p[i * 32 * 4];
  }
  png_set_rows(p, info_ptr, img_rows);
  png_set_write_fn(p, &png_buffer, [](png_structp ptr, png_bytep data, png_size_t length){
    string *p = (string*)png_get_io_ptr(ptr);
    p->insert(p->size(), (char*)data, length);
  }, NULL);
  png_write_png(p, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  image = png_buffer;
  png_destroy_write_struct(&p, &info_ptr);
  return true;
}

void Sprite::toBase64(){
  static const char tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
  string ret_buf;
  uint32_t buf;
  size_t l = image.size();
  for(size_t i=3;i<l;i+=3){
    buf = (uint8_t)image[i - 3];
    buf <<= 8;
    buf |= (uint8_t)image[i - 2];
    buf <<= 8;
    buf |= (uint8_t)image[i - 1];
    ret_buf += tab[(buf>>18)&63];
    ret_buf += tab[(buf>>12)&63];
    ret_buf += tab[(buf>>6)&63];
    ret_buf += tab[(buf)&63];
  }
  size_t pd = l % 3;
  if(pd == 2){
    buf = (uint8_t)image[l - 2];
    buf <<= 8;
    buf |= (uint8_t)image[l - 1];
    buf <<= 8;
    ret_buf += tab[(buf>>18)&63];
    ret_buf += tab[(buf>>12)&63];
    ret_buf += tab[(buf>>6)&63];
    ret_buf += '=';
  }else if(pd == 1){
    buf = (uint8_t)image[l - 1];
    buf <<= 8;
    ret_buf += tab[(buf>>10)&63];
    ret_buf += tab[(buf>>4)&63];
    ret_buf += "==";
  }
  image = ret_buf;
}

SpriteLoader::SpriteLoader(std::string path){
  BinaryFile spr(path);
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
  offset_to_data = spr.getOffset();
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
  //cache rest of file
  spr.goToOffset(offset_to_data);
  spr.readRest(buffer);
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
  size_t offset_read = sp.offset + 5 - offset_to_data;
  //cout<<"offset "<<sp.offset<<" buffer offset "<<offset_read<<endl;
  uint32_t pixel_offset = 0;
  sp.image.resize(4*32*32, '\0');
  size_t data_left = sp.size;
  uint32_t blank, datas;
  while(data_left>0){
    if(data_left<4){
      error = "cannot read header of sprite ";
      return "";
    }
    blank = (uint8_t)buffer[offset_read + 1];
    blank <<= 8;
    blank |= (uint8_t)buffer[offset_read];
    pixel_offset += blank * 4;
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
      sp.image[pixel_offset+0] = buffer[offset_read];
      sp.image[pixel_offset+1] = buffer[offset_read + 1];
      sp.image[pixel_offset+2] = buffer[offset_read + 2];
      sp.image[pixel_offset+3] = 255;
      pixel_offset += 4;
      offset_read += 3;
    }
    data_left -= datas * 3;
  }
  if(!sp.RawToPng()){
    error="cannot convert raw to png";
    return "";
  }

  /*
  std::string out_path="i";
  out_path += to_string(id);
  out_path += ".png";
  fstream out(out_path, ios::binary|ios::trunc|ios::out);
  cout<<"out "<<out_path<<" is "<<(out.good()?"true":"false")<<endl;
  out.write(sp.image.data(), sp.image.size());
  //*/
  sp.toBase64();
  sp.loaded = true;
  return sp.getImage();
}
