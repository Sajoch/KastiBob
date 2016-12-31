#include "file.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
  if(argc!=2){
    cout<<"using: "<<argv[0]<<" <sprfile>"<<endl;
    return 1;
  }
  BinaryFile spr(argv[1]);
  vector<Sprite> headers;
  if(!spr.possibleRead(4)){
    cout<<"cannot read signature"<<endl;
    return 2;
  }
  uint32_t signature = spr.getUint32();
  if(!spr.possibleRead(2)){
    cout<<"cannot read spriteCount"<<endl;
    return 3;
  }
  uint16_t spriteCount = spr.getUint16();
  cout<<"Signature: "<<signature<<endl;
  cout<<"Sprites: "<<spriteCount<<endl;
  for(uint16_t id=0;id<spriteCount;id++){
    if(!spr.possibleRead(4)){
      cout<<"cannot read offset of header of sprite"<<endl;
      return 4;
    }
    Sprite sp;
    sp.offset = spr.getUint32();
    sp.loaded = false;
    headers.push_back(sp);
  }
  for(vector<Sprite>::iterator it=headers.begin();it!=headers.end();++it){
    if((*it).offset == 0)
      continue;
    (*it).loaded = true;
    spr.goToOffset((*it).offset);
    if(!spr.possibleRead(5)){
      cout<<"cannot read header of sprite "<<endl;
      return 5;
    }
    (*it).unk[0] = spr.getUint8();
    (*it).unk[1] = spr.getUint8();
    (*it).unk[2] = spr.getUint8();
    (*it).size = spr.getUint16();
    if((*it).size > 3444){
      cout<<"has too big size"<<endl;
      return 6;
    }
    size_t offset_read = 0;
    uint32_t pixelOffset = 0;
    (*it).image = new uint8_t[3*32*32];

    while(offset_read < (*it).size){
      if(!spr.possibleRead(4)){
        cout<<"cannot read header of sprite "<<endl;
        return 7;
      }
      uint16_t transpixelscount = spr.getUint16();
      pixelOffset += transpixelscount*3;
      offset_read += 2;
      if(transpixelscount > 3076){
        cout<<"has too big pixel chunk"<<transpixelscount<<endl;
        return 8;
      }
      uint16_t pixelscount = spr.getUint16();
      offset_read += 2;
      if(pixelscount > 3076){
        cout<<"has too big pixel chunk"<<pixelscount<<endl;
        return 9;
      }
      uint8_t rgb[3];
      for(uint16_t ip=0;ip<pixelscount;ip++){
        if(!spr.possibleRead(3)){
          cout<<"cannot read rgb of sprite "<<endl;
          return 9;
        }
        rgb[0] = spr.getUint8();
        rgb[1] = spr.getUint8();
        rgb[2] = spr.getUint8();
        (*it).image[pixelOffset+0] = rgb[0];
        (*it).image[pixelOffset+1] = rgb[1];
        (*it).image[pixelOffset+2] = rgb[2];
        pixelOffset++;
        offset_read += 3;
      }
    }
    //break;
  }
}
