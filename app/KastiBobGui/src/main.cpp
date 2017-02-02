#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QThread>
#include "runmain.hpp"
#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include "config.hpp"
#include "datLoader.hpp"
#include <iostream>

using namespace std;

//TODO no global
class Client* tclient = 0;
ConfigFile* paths;

class LoaderThread: public QThread{
public:
  LoaderThread(DatLoader* _dat, std::string _path){
    dat = _dat;
    path = _path;
  }
private:
  DatLoader* dat;
  std::string path;
  void run(){
    dat->load(path);
  }
};

RunMain::RunMain(){
  lf = 0;
  cs = 0;
  gw = 0;
  datobjs = new DatLoader();
  stateLoadedResources = false;
  std::string dat_path = paths->getVal("DAT_FILE","../../kclient_v1/Kasti.dat");
  lt = new LoaderThread(datobjs, dat_path);
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
  LoginForm* new_lf = new LoginForm();
  delAllWindows();
  lf = new_lf;
  lf->load();
  if(stateLoadedResources){
    lf->resourcesLoaded();
  }
}
void RunMain::GoToCharSelect(){
  CharSelect* new_cs = new CharSelect();
  delAllWindows();
  cs = new_cs;
  cs->load();
}
void RunMain::GoToGameWindow(){
  GameWindow* new_gw = new GameWindow();
  delAllWindows();
  gw = new_gw;
  gw->load();
}
DatLoader* RunMain::getDatobjs(){
  return datobjs;
}

RunMain* app;

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    paths = new ConfigFile("path.cfg");
    app = new RunMain();
    app->GoToLoginForm();
    return Qapp.exec();
}
