#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "uis_cpp/gamewindow.gen.h"
#include <QtWidgets/QMainWindow>
#include "jsbrige.h"


class GameWindow : public QMainWindow

{

  void attachObject();

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private:
    Ui_GameWindow* ui;
    JSBrige* brige;
};

#endif // _GAMEWINDOW_H
