#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>
#include "charselect.h"
#include "gamewindow.h"
#include "loginform.h"
#include "jsbridge.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui_GameWindow();
    ui->setupUi(this);
    bridge = new JSBridge(this);
    bridge->setGW(this);

    QWebPage* page = ui->webView->page();
    QWebFrame* frame = page->mainFrame();
    page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    frame->addToJavaScriptWindowObject("JSBridge", bridge);
    connect(frame, &QWebFrame::javaScriptWindowObjectCleared, this, &GameWindow::attachObject);
}
void GameWindow::attachObject(){
  QWebPage* page = ui->webView->page();
  QWebFrame* frame = page->mainFrame();
  frame->addToJavaScriptWindowObject("JSBridge", bridge);
}

void GameWindow::logout(){
  LoginForm* tmp = new LoginForm();
  delete this;
  tmp->show();
}

void GameWindow::charSelect(){
  CharSelect* tmp = new CharSelect();
  delete this;
  tmp->show();
}

GameWindow::~GameWindow(){
    delete bridge;
    delete ui;
}
