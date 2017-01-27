#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "gamewindow.gen.h"
#include <QtWidgets/QMainWindow>


class GameWindow : public QMainWindow{
  Q_OBJECT
public:
  explicit GameWindow(QWidget *parent = 0);
  ~GameWindow();
  
  bool calledExec;
  bool loaded_page;
  
  void load();
  bool close();
  void loaded();
signals:
  void logout();
  void charSelect();
private:
  Ui_GameWindow* ui;
  class JSBridge* bridge;
  void attachObject();
};

#endif // _GAMEWINDOW_H
