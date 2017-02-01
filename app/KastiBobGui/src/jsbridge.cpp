#include "jsbridge.h"
#include "gamewindow.h"
#include "client.hpp"
#include "spriteLoader.hpp"
#include "config.hpp"
#include <QtCore/QVariant>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include <QtCore/QTimer>


using namespace std;

extern Client* tclient;
extern ConfigFile* paths;

JSBridge::JSBridge(QObject *parent) : QObject(parent){
  std::string spr_path = paths->getVal("SPR_FILE","../../kclient_v1/Kasti.spr");
  sprs = new SpriteLoader(spr_path);
  connect(this, &JSBridge::sendData, this, &JSBridge::sendDataToJS);
  
  connect(this, &JSBridge::errorMsg, this, [&](std::string msg){
    QMessageBox msgBox;
    cout<<"error xD "<<msg<<endl;
    msgBox.setText(QString::fromStdString(msg));
    msgBox.exec();
  });
  
}

void JSBridge::setGW(GameWindow* that, QWebView* _webView){
  gamewindow = that;
  webView = _webView;
  mframe = webView->page()->currentFrame();
  mframe->addToJavaScriptWindowObject("JSBridge", this);
  mframe->evaluateJavaScript("start();");
  tclient->afterError([&](std::string msg){
    errorMsg(msg);
  });
  tclient->enter();
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
  return QString::fromStdString(buf);
}
void JSBridge::start(){
  CrossCallAfterUpdate();
  tclient->afterRecv([&](){
    CrossCallAfterUpdate();
  });
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
  json = QString("Communication.update(%1)").arg(json);
  sendData(json);
}
void JSBridge::sendDataToJS(QString json){
  mframe->evaluateJavaScript(json);
}