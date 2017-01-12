#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QTimer>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "client.hpp"
#include <iostream>

using namespace std;

Client* tclient = 0;
QTimer *logic_loop;
LoginForm* lf;
CharSelect* cs;
GameWindow* gw;

void GoToLoginForm();
void GoToCharSelect();
void GoToGameWindow();

void GoToLoginForm(){
  QTimer::singleShot(0, [](){
    lf->show();
    cs->hide();
    gw->hide();
    lf->load();
    logic_loop->stop();
  });
}
void GoToCharSelect(){
  QTimer::singleShot(0, [](){
    cs->show();
    lf->hide();
    gw->hide();
    cs->load();
    logic_loop->stop();
  });
}
void GoToGameWindow(){
  QTimer::singleShot(0, [](){
    gw->show();
    cs->hide();
    lf->hide();
    gw->load();
  });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* list resources entry
    QStringList resources = QDir(":").entryList();
    for(int i =0;i<resources.size();i++){
      cout<<resources.at(i).toUtf8().constData()<<endl;
    }
    */
    lf = new LoginForm();
    cs = new CharSelect();
    gw = new GameWindow();
    logic_loop = new QTimer();
    QObject::connect(logic_loop, &QTimer::timeout, [&](){
      if(tclient->tick()==0){
        logic_loop->stop();
      }
    });
    GoToLoginForm();
    return a.exec();
}
