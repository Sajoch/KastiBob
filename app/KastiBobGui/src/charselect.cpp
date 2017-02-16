#include "charselect.h"
#include "client.hpp"
#include "runmain.hpp"

<<<<<<< HEAD
CharSelect::CharSelect(RunMain* app) :
    QDialog(0), 
    runapp(app),
    loginConf("login.cfg"){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  
  rChar = loginConf.getVal("CHAR", 0);
  rAutoChar = loginConf.getVal("AUTOCHAR", 0);
  
=======
extern RunMain* app;
extern Client* tclient;

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  connect(ui->pushButton, &QPushButton::clicked, this, &CharSelect::logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &CharSelect::enter);
  
  connect(this, &CharSelect::logouted, app, &RunMain::GoToLoginForm);
  connect(this, &CharSelect::entered, app, &RunMain::GoToGameWindow);
<<<<<<< HEAD
  connect(this, &CharSelect::errorMsg, app, &RunMain::errorMsg);
=======
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
}

void CharSelect::load(){
  while(ui->comboBox->count()>0){
    ui->comboBox->removeItem(0);
  }
<<<<<<< HEAD
  runapp->getClient()->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), (quint64)id);
  });
  ui->comboBox->setCurrentIndex(rChar);
  runapp->getClient()->afterError([&](std::string msg, std::string type){
    //errorMsg(QString::fromStdString(msg), QString::fromStdString(type));
  });
  if(rAutoChar){
    //enter();
  }
=======
  tclient->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), (quint64)id);
  });
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  show();
}

void CharSelect::enter(){
  size_t id = ui->comboBox->currentData().toULongLong();
<<<<<<< HEAD
  loginConf.setVal("CHAR", ui->comboBox->currentIndex());
  if(runapp->getClient()->setChar(id)){
=======
  if(tclient->setChar(id)){
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
    entered();
  }else{
    logout();
  }
}

void CharSelect::logout(){
<<<<<<< HEAD
  delete runapp->getClient();
=======
  delete tclient;
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
  logouted();
}

void CharSelect::keyPressEvent(QKeyEvent *e) {
  if(e->key() != Qt::Key_Escape){
    QDialog::keyPressEvent(e);
  } else {

  }
}

CharSelect::~CharSelect()
{
  runapp->getClient()->clearCallbacks();
}
