#include "jsbridge.h"
#include "gamewindow.h"
#include "client.hpp"
#include "spriteLoader.hpp"
#include <QtCore/QVariant>
#include <iostream>


using namespace std;

extern Client* tclient;

JSBridge::JSBridge(QObject *parent) : QObject(parent){
  tclient->afterRecv([&](){
    CrossCallAfterUpdate();
  });
  sprs = new SpriteLoader("..\\..\\kclient_v1\\Kasti.spr");
}

void JSBridge::setGW(GameWindow* that, QWebView* _webView){
  gamewindow = that;
  mframe = _webView->page()->mainFrame();
}

void JSBridge::CrossCallAfterUpdate(){
  QVariantMap hero;
  QVariantMap pos;
  pos["x"] = tclient->getX();
  pos["y"] = tclient->getY();
  pos["z"] = tclient->getZ();
  hero["pos"] = pos;
  QVariantMap obj;
  obj["hero"] = hero;
  callAfterUpdate(obj);

}

void JSBridge::logout(){
  delete tclient;
  delete sprs;
  gamewindow->logout();
}

void JSBridge::charSelect(){
  tclient->setChar(0);
  gamewindow->charSelect();
}

QString JSBridge::getImg(int id){
  std::string buf = sprs->getImage(id);
  cout<<sprs->getError()<<endl;
  return QString::fromStdString(buf);
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
void JSBridge::look(int id){

}
void JSBridge::callAfterUpdate(QVariant data){
  QJsonDocument doc = QJsonDocument::fromVariant(data);
  QString json = doc.toJson(QJsonDocument::Compact);
  cout<<json.toStdString()<<endl;
  QString cmd = QString("Communication.update(%1)").arg(json);
  mframe->evaluateJavaScript(cmd);
}