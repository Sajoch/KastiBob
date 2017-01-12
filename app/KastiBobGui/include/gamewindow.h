#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "gamewindow.gen.h"
#include <QtWidgets/QMainWindow>


class GameWindow : public QMainWindow{
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void logout();
    void charSelect();
    void load();
    bool close();
private:
    Ui_GameWindow* ui;
    class JSBridge* bridge;
    void attachObject();
};

#endif // _GAMEWINDOW_H
