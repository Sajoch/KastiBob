#include "moc_h/jsbridge.gen.h"
#include "gamewindow.h"
#include "src/client.hpp"

extern Client* tclient;

JSBridge::JSBridge(QObject *parent) : QObject(parent){
  tclient->afterRecv([&](){
    callAfterUpdate();
  });
}

void JSBridge::setGW(GameWindow* that){
  gamewindow = that;
}

void JSBridge::logout(){
  gamewindow->logout();
}

void JSBridge::charSelect(){
  gamewindow->charSelect();
}

QString JSBridge::getImg(size_t id){
    return "test123";
}
void JSBridge::move(int dir){
  switch(dir){
    case 1: //up
      tclient->move(ClientDirectory::NORTH);
    break;
    case 2://down
      tclient->move(ClientDirectory::SOUTH);
    break;
    case 3://left
      tclient->move(ClientDirectory::WEST);
    break;
    case 4://right
      tclient->move(ClientDirectory::EAST);
    break;
  }
}
void JSBridge::look(uint32_t id){

}

uint32_t JSBridge::getX(){
  return tclient->getX();
}
uint32_t JSBridge::getY(){
  return tclient->getY();
}
void JSBridge::callAfterUpdate(){

}
