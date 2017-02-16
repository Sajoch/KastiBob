#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "gamewindow.gen.h"
#include <QtWidgets/QMainWindow>


class GameWindow : public QMainWindow{
  Q_OBJECT
public:
  explicit GameWindow(class RunMain* app);
  ~GameWindow();
  
  void load();
  bool close();
signals:
  void logout();
  void charSelect();
  void errorMsg(QString msg);
private:
  class RunMain* runapp;
  class RenderArea* render;
  Ui_GameWindow* ui;
  void attachObject();
};

#endif // _GAMEWINDOW_H
