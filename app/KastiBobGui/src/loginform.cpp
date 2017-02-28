#include <functional>
#include <iostream>
#include <QtWidgets/QApplication>
#include "loginform.h"
#include "runmain.hpp"
#include "client.hpp"
#include "datLoader.hpp"

LoginForm::LoginForm(RunMain* app) :
    QDialog(0), 
    runapp(app),
    loginConf("login.cfg")
{
  ui = new Ui_LoginForm();
  ui->setupUi(this);
  ConfigFile listServ("list.cfg");
  listServ.each([&](std::string name, std::string val){
    ui->comboBox->addItem(QString::fromStdString(name), QString::fromStdString(val));
  });

  rServer = loginConf.getVal("SERVER", 0);
  rLogin = loginConf.getVal("LOGIN", "");
  rAutoLogin = loginConf.getVal("AUTOLOGIN", 0);
  if(rAutoLogin){
    rPassword = loginConf.getVal("PASSWORD", "");
  }
  
  connect(ui->pushButton_2, &QPushButton::clicked, this, &LoginForm::login);
  connect(ui->pushButton, &QPushButton::clicked, this, &LoginForm::exit);
  
  connect(this, &LoginForm::logged, app, &RunMain::GoToCharSelect);
  connect(this, &LoginForm::errorMsg, app, &RunMain::errorMsg);
}

void LoginForm::setProgess(double a){
	ui->progressBar->setValue(a*100);
}

void LoginForm::load(){
  ui->retranslateUi(this);
  changeLoginState(2, "loading resources");
  ui->comboBox->setCurrentIndex(rServer);
  if(!rLogin.empty()){
    ui->lineEdit_2->setText(QString::fromStdString(rLogin));
    ui->lineEdit->setFocus();
  }else{
    ui->lineEdit_2->setFocus();
  }
  if(rAutoLogin && !rPassword.empty()){
    ui->lineEdit->setText(QString::fromStdString(rPassword));
    login();
  }
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
      logged();
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
  loginConf.setVal("SERVER", ui->comboBox->currentIndex());
  loginConf.setVal("LOGIN", ls);
  runapp->getClient(new Client(sa, 20007, 2, ls, ps, runapp->getDatobjs()));
  runapp->getClient()->afterError([&](std::string msg, std::string type){
    errorMsg(QString::fromStdString(msg), QString::fromStdString(type));
  });
  runapp->getClient()->loginListener([&](int a, std::string msg){
    changeLoginState(a, msg);
  });
}

void LoginForm::exit(){
  reject();
}

void LoginForm::resourcesLoaded(){
  changeLoginState(2, "Resources loaded");
}

void LoginForm::keyPressEvent(QKeyEvent *e) {
  if(e->key() != Qt::Key_Escape){
      QDialog::keyPressEvent(e);
  } else {

  }
}

LoginForm::~LoginForm(){
  runapp->getClient()->clearCallbacks();
  delete ui;
}
