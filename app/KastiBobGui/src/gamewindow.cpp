#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>
#include "gamewindow.h"
#include "jsbridge.h"


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui_GameWindow();
    ui->setupUi(this);
    QWebPage* page = ui->webView->page();
    page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}
void GameWindow::load(){
  bridge = new JSBridge(this);
  bridge->setGW(this, ui->webView);
  QWebPage* page = ui->webView->page();
  QWebFrame* frame = page->mainFrame();
  frame->addToJavaScriptWindowObject("JSBridge", bridge);
  frame->evaluateJavaScript("start();");
}

void GameWindow::logout(){
  //GoToLoginForm();
}

void GameWindow::charSelect(){
  //GoToCharSelect();
}

bool GameWindow::close(){
  return true;
}

GameWindow::~GameWindow(){
  delete bridge;
  delete ui;
}
