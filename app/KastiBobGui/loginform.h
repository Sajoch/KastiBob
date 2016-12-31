#ifndef _LOGINFORM_H
#define _LOGINFORM_H

#include "uis_cpp/loginform.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>

class LoginForm : public QDialog{
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
private:
  Ui_LoginForm* ui;
};

#endif // LOGINFORM_H
