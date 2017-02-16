#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>
#include "gamewindow.h"
<<<<<<< HEAD
#include "renderarea.hpp"
#include "sprLoader.hpp"
#include "runmain.hpp"
#include "client.hpp"
#include <iostream>

using namespace std;
=======
#include "jsbridge.h"
#include "runmain.hpp"
#include <iostream>

using namespace std;

extern RunMain* app;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa

GameWindow::GameWindow(RunMain* app) :
    QMainWindow(0),
    runapp(app)
{
<<<<<<< HEAD
  ui = new Ui_GameWindow();
  ui->setupUi(this);
  render = new RenderArea(this, runapp);
  ui->horizontalLayout->addWidget(render);
  connect(this, &GameWindow::logout, runapp, &RunMain::GoToLoginForm);
  connect(this, &GameWindow::charSelect, runapp, &RunMain::GoToGameWindow);
}
void GameWindow::load(){
  show();
  runapp->getClient()->enter();
=======
    ui = new Ui_GameWindow();
    ui->setupUi(this);
    QWebPage* page = ui->webView->page();
    page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    
    connect(this, &GameWindow::logout, app, &RunMain::GoToLoginForm);
    connect(this, &GameWindow::charSelect, app, &RunMain::GoToGameWindow);
    
    connect(page, &QWebPage::loadFinished, this, &GameWindow::loaded);
    calledExec = false;
    loaded_page = false;
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
  QWebPage* page = ui->webView->page();
  QWebFrame* frame = page->mainFrame();
  frame->addToJavaScriptWindowObject("JSBridge", bridge);
  frame->evaluateJavaScript("start();");
  show();
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}

bool GameWindow::close(){
  return true;
}

GameWindow::~GameWindow(){
  delete ui;
}
