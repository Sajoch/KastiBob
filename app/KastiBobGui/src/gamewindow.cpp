#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>
#include "gamewindow.h"
#include "jsbridge.h"
#include "runmain.hpp"
#include <iostream>

using namespace std;

extern RunMain* app;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
  ui = new Ui_GameWindow();
  ui->setupUi(this);
  QWebPage* page = ui->webView->page();
  //ui->webView->setContextMenuPolicy(Qt::CustomContextMenu);
  page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
  
  connect(this, &GameWindow::logout, app, &RunMain::GoToLoginForm);
  connect(this, &GameWindow::charSelect, app, &RunMain::GoToGameWindow);
  
  calledExec = false;
  loaded_page = false;
  connect(page, &QWebPage::loadFinished, this, &GameWindow::loaded);
}
void GameWindow::loaded(){
  loaded_page = true;
  if(calledExec){
    load();
    calledExec = false;
  }
}
void GameWindow::load(){
  if(!loaded_page){
    calledExec = true;
    return;
  }
  bridge = new JSBridge(this);
  bridge->setGW(this, ui->webView);
  show();
}

bool GameWindow::close(){
  return true;
}

GameWindow::~GameWindow(){
  delete bridge;
  delete ui;
}
