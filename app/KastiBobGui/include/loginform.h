#ifndef _LOGINFORM_H
#define _LOGINFORM_H

#include "loginform.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>
#include "config.hpp"

class LoginForm : public QDialog{
  
  Q_OBJECT
  
public:
  explicit LoginForm(class RunMain* app);
  ~LoginForm();
  void load();
  void login();
  void exit();
  void resourcesLoaded();
  void selectServer();
  void keyPressEvent(QKeyEvent *e);
  void changeLoginState(int a, std::string msg);
signals:
  void logged();
<<<<<<< HEAD
  void errorMsg(QString msg, QString type);
=======
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
private:
  class RunMain* runapp;
  ConfigFile loginConf;
  size_t rServer;
  std::string rLogin;
  int rAutoLogin;
  std::string rPassword;
  Ui_LoginForm* ui;
};

#endif // LOGINFORM_H
