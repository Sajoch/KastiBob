#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "runmain.hpp"
#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include <iostream>

using namespace std;

class Client* tclient = 0;

RunMain::RunMain(){
  lf = 0;
  cs = 0;
  gw = 0;
}

RunMain::~RunMain(){
  delAllWindows();
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
  lf = new LoginForm();
  lf->load();
}
void RunMain::GoToCharSelect(){
  delAllWindows();
  cs = new CharSelect();
  cs->load();
}
void RunMain::GoToGameWindow(){
  delAllWindows();
  gw = new GameWindow();
  gw->load();
}

RunMain* app;

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    app = new RunMain();
    app->GoToLoginForm();
    return Qapp.exec();
}
