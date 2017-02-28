#include "jsbridge.h"
#include "gamewindow.h"
#include "runmain.hpp"
#include "client.hpp"
#include "sprLoader.hpp"
#include "config.hpp"
#include <QtCore/QVariant>
#include <iostream>
#include <QtCore/QTimer>


using namespace std;

extern ConfigFile* paths;

JSBridge::JSBridge(GameWindow* that, QWebView* _webview, RunMain* app): 
QObject(0),
runapp(app)
{
	connect(this, &JSBridge::sendData, this, &JSBridge::sendDataToJS);
	connect(this, &JSBridge::errorMsg, app, &RunMain::errorMsg);
	gamewindow = that;
	webView = _webview;
	mframe = webView->page()->currentFrame();
	mframe->addToJavaScriptWindowObject("JSBridge", this);
	mframe->evaluateJavaScript("start();");
	//runapp->getClient()->afterError([&](std::string msg, std::string type){
		//cout<<type<<": "<<msg<<endl;
		//errorMsg(QString::fromStdString(msg), QString::fromStdString(type));
	//});
	//runapp->getClient()->afterDisconnect([&](){
		//cout<<"reconnecting"<<endl;
		//runapp->getClient()->enter();
	//});
	runapp->getClient()->enter();
}
JSBridge::~JSBridge(){
  //app->getClient()->clearCallbacks();
}

void JSBridge::CrossCallAfterUpdate(){
	QVariantMap hero;
	QVariantMap pos;
	pos["x"] = runapp->getClient()->getX();
	pos["y"] = runapp->getClient()->getY();
	pos["z"] = runapp->getClient()->getZ();
	hero["pos"] = pos;
	QVariantMap obj;
	obj["hero"] = hero;
	QVariantMap map;
	
	
	obj["map"] = map;
	callAfterUpdate(obj);
}

void JSBridge::logout(){
  //gamewindow->logout();
}

void JSBridge::charSelect(){
  //app->getClient()->setChar(0);
  //gamewindow->charSelect();
}

QString JSBridge::getImg(int id){
  std::string buf = runapp->getSpr()->getImage(id);
  return QString::fromStdString(buf);
}
void JSBridge::start(){
  CrossCallAfterUpdate();
  //app->getClient()->afterRecv([&](){
    //CrossCallAfterUpdate();
  //});
}
void JSBridge::move(int dir){
  switch(dir){
    case 1: //up
      //app->getClient()->move(ClientDirectory::NORTH);
    break;
    case 2://down
      //app->getClient()->move(ClientDirectory::SOUTH);
    break;
    case 3://left
      //app->getClient()->move(ClientDirectory::WEST);
    break;
    case 4://right
      //app->getClient()->move(ClientDirectory::EAST);
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