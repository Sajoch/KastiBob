#include "loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent)
{
  ui = new Ui_LoginForm();
  ui->setupUi(this);
}

LoginForm::~LoginForm()
{
  delete ui;
}
