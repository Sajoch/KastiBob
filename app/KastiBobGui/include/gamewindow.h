#ifndef _GAMEWINDOW_H
#define _GAMEWINDOW_H
#include "gamewindow.gen.h"
#include <QtWidgets/QMainWindow>


class GameWindow : public QMainWindow{
	Q_OBJECT
public:
	explicit GameWindow(class RunMain* app);
	~GameWindow();
	bool calledExec;
	bool loaded_page;
	void load();
	bool close();
signals:
	void logout();
	void charSelect();
	void errorMsg(QString msg);
private:
	void loaded();
	class RunMain* runapp;
	Ui_GameWindow* ui;
	class JSBridge* bridge;
	void attachObject();
};

#endif // _GAMEWINDOW_H
