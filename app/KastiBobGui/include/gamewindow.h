#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "gamewindow.gen.h"
#include <QtWidgets/QMainWindow>


class GameWindow : public QMainWindow{
  Q_OBJECT
public:
<<<<<<< HEAD
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
=======
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
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  void attachObject();
};

#endif // _GAMEWINDOW_H
