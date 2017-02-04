#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QThread>
#include <QtWidgets/QMessageBox>
#include "runmain.hpp"
#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include "config.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include <iostream>

using namespace std;

//TODO no global
class Client* tclient = 0;

class LoaderThread: public QThread{
public:
  LoaderThread(DatLoader* _dat, SpriteLoader* _spr){
    dat = _dat;
    spr = _spr;
  }
private:
  DatLoader* dat;
  SpriteLoader* spr;
  void run(){
    dat->load();
    spr->load();
  }
};

RunMain::RunMain(){
  lf = 0;
  cs = 0;
  gw = 0;
  paths = new ConfigFile("path.cfg");
  std::string dat_path = paths->getVal("DAT_FILE","../../kclient_v1/Kasti.dat");
  std::string spr_path = paths->getVal("SPR_FILE","../../kclient_v1/Kasti.spr");
  datobjs = new DatLoader(dat_path);
  sprobjs = new SpriteLoader(spr_path);
  stateLoadedResources = false;
  lt = new LoaderThread(datobjs, sprobjs);
  connect(lt, &LoaderThread::finished, this, &RunMain::loadedResources);
  lt->start();
}

RunMain::~RunMain(){
  delAllWindows();
  if(datobjs != 0){
    delete datobjs;
  }
  delete lt;
}

void RunMain::loadedResources(){
  if(lf != 0){
    lf->resourcesLoaded();
  }
  stateLoadedResources = true;
}

void RunMain::delAllWindows(){
  if(lf != 0){
    delete lf;
    lf = 0;
  }
  if(cs != 0){
    delete cs;
    cs = 0;
  }
  if(gw != 0){
    delete gw;
    gw = 0;
  }
}

void RunMain::GoToLoginForm(){
  delAllWindows();
  lf = new LoginForm(this);
  lf->load();
  if(stateLoadedResources){
    lf->resourcesLoaded();
  }
}
void RunMain::GoToCharSelect(){
  delAllWindows();
  cs = new CharSelect(this);
  cs->load();
}
void RunMain::GoToGameWindow(){
  delAllWindows();
  gw = new GameWindow(this);
  gw->load();
}
DatLoader* RunMain::getDatobjs(){
  return datobjs;
}

SpriteLoader* RunMain::getSpr(){
  return sprobjs;
}
Client* RunMain::getClient(){
  return tclient;
}
Client* RunMain::getClient(Client* v){
  tclient = v;
  return tclient;
}

void RunMain::errorMsg(QString msg){
  QMessageBox msgBox;
  msg = QApplication::translate("ErrorMsg", msg.toUtf8().data(), 0);
  msgBox.setText(msg);
  msgBox.exec();
}

RunMain* app;

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    RunMain* app = new RunMain();
    app->GoToLoginForm();
    return Qapp.exec();
}
