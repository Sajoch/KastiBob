#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QDir>
#include <QtCore/QStringList>
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


RunMain::RunMain(){
  lf = 0;
  cs = 0;
  gw = 0;
  datobjs = 0;
}

RunMain::~RunMain(){
  delAllWindows();
  if(datobjs != 0){
    delete datobjs;
  }
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
}
void RunMain::GoToCharSelect(){
  CharSelect* new_cs = new CharSelect();
  if(datobjs == 0){
    std::string dat_path = paths->getVal("DAT_FILE","../../kclient_v1/Kasti.dat");
    datobjs = new DatLoader(dat_path);
  }
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

RunMain* app;

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    paths = new ConfigFile("path.cfg");
    app = new RunMain();
    app->GoToLoginForm();
    return Qapp.exec();
}
