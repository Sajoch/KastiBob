#ifndef _LOGINFORM_H
#define _LOGINFORM_H

#include "loginform.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>
#include "config.hpp"

class LoginForm : public QDialog{
  
  Q_OBJECT
  
public:
  explicit LoginForm(QWidget *parent = 0);
  ~LoginForm();
  void load();
  void login();
  void exit();
  void selectServer();
  void keyPressEvent(QKeyEvent *e);
  void changeLoginState(int a, std::string msg);
signals:
  void logged();
private:
  ConfigFile loginConf;
  size_t rServer;
  std::string rLogin;
  Ui_LoginForm* ui;
};

#endif // LOGINFORM_H
