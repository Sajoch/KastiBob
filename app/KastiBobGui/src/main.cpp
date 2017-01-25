#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QTimer>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "client.hpp"
#include "runmain.hpp"
#include <iostream>

using namespace std;

Client* tclient = 0;

RunMain::RunMain(int argc, char** argv){
  a = new QApplication(argc, argv);
  lf = 0;
  cs = 0;
  gw = 0;
}

int RunMain::ret(){
  lf = new LoginForm();
  lf->load();
  return a->exec();
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
    app = new RunMain(argc, argv);
    app->GoToLoginForm();
    return app->ret();
}
