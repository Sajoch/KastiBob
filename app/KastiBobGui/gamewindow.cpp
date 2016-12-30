#include "gamewindow.h"
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebPage>
#include <QtCore/QUrl>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui_GameWindow();
    ui->setupUi(this);
    brige = new JSBrige();

    QWebPage* page = ui->webView->page();
    QWebFrame* frame = page->mainFrame();
    page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    frame->load(QUrl("qrc:/index.html"));
    attachObject();
    connect(frame, &QWebFrame::javaScriptWindowObjectCleared, this, &GameWindow::attachObject);
}
void GameWindow::attachObject(){
  QWebPage* page = ui->webView->page();
  QWebFrame* frame = page->mainFrame();
  frame->addToJavaScriptWindowObject("JSBrige", brige );
}

GameWindow::~GameWindow(){
    delete brige;
    delete ui;
}
