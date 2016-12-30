#include "moc_h/jsbridge.gen.h"
#include "gamewindow.h"

JSBridge::JSBridge(QObject *parent) : QObject(parent){

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

}
void JSBridge::look(uint32_t id){

}
