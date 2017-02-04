#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>
#include "gamewindow.h"
#include "renderarea.hpp"
#include "sprLoader.hpp"
#include "runmain.hpp"
#include "client.hpp"
#include <iostream>

using namespace std;

GameWindow::GameWindow(RunMain* app) :
    QMainWindow(0),
    runapp(app)
{
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
}

bool GameWindow::close(){
  return true;
}

GameWindow::~GameWindow(){
  delete ui;
}
