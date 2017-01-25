#include <functional>
#include <QtWidgets/QApplication>
#include <QtCore/QTimer>
#include "loginform.h"
#include "runmain.hpp"
#include "client.hpp"

extern RunMain* app;
extern Client* tclient;

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent)
{
  ui = new Ui_LoginForm();
  ui->setupUi(this);
  //TODO outside
  ui->comboBox->addItem("Kasteria.net", "91.134.189.246:7171");
  ui->comboBox->addItem("Tibijka.net", "178.32.162.105:7171");
  connect(ui->pushButton_2, &QPushButton::clicked, this, &LoginForm::login);
  connect(ui->pushButton, &QPushButton::clicked, this, &LoginForm::exit);
  
  connect(this, &LoginForm::logged, app, &RunMain::GoToCharSelect);
}

void LoginForm::load(){
  ui->retranslateUi(this);
  ui->lineEdit_2->setFocus();
  show();
}

void LoginForm::changeLoginState(int a, std::string msg){
  switch(a){
    case 1:
      ui->label->setText(QApplication::translate("LoginForm", "logging", 0));
    break;
    case 2:
      ui->label->setText(msg.c_str());
    break;
    case 3:
      ui->label->setText(QApplication::translate("LoginForm", "connection problem", 0));
    break;
    case 4:
      ui->label->setText(QApplication::translate("LoginForm", "logged", 0));
      //GoToCharSelect();
    break;
    default:
      ui->label->setText(QApplication::translate("LoginForm", "unexpected error", 0));
    break;
  }
}

void LoginForm::login(){
  QString l = ui->lineEdit_2->text();
  QString p = ui->lineEdit->text();
  std::string ls = l.toUtf8().constData();
  std::string ps = p.toUtf8().constData();
  changeLoginState(1, "");
  std::string sa = ui->comboBox->currentData().toString().toUtf8().constData();
  tclient = new Client(sa, 20007, 2, ls, ps);
  tclient->loginListener([&](int a, std::string msg){
    changeLoginState(a, msg);
  });
}

void LoginForm::exit(){
  reject();
}

void LoginForm::keyPressEvent(QKeyEvent *e) {
  if(e->key() != Qt::Key_Escape){
      QDialog::keyPressEvent(e);
  } else {

  }
}

LoginForm::~LoginForm(){
  delete ui;
}
