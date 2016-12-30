#ifndef _LOGINFORM_H
#define _LOGINFORM_H

#include "uis_cpp/loginform.gen.h"
#include <QtWidgets/QDialog>

class LoginForm : public QDialog
{


public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:
  Ui_LoginForm* ui;
};

#endif // LOGINFORM_H
