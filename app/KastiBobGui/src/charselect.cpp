#include "charselect.h"
#include "client.hpp"
#include "runmain.hpp"

CharSelect::CharSelect(RunMain* app) :
    QDialog(0), 
    runapp(app),
    loginConf("login.cfg"){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  
  rChar = loginConf.getVal("CHAR", 0);
  rAutoChar = loginConf.getVal("AUTOCHAR", 0);
  
  connect(ui->pushButton, &QPushButton::clicked, this, &CharSelect::logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &CharSelect::enter);
  
  connect(this, &CharSelect::logouted, app, &RunMain::GoToLoginForm);
  connect(this, &CharSelect::entered, app, &RunMain::GoToGameWindow);
  connect(this, &CharSelect::errorMsg, app, &RunMain::errorMsg);
}

void CharSelect::load(){
  while(ui->comboBox->count()>0){
    ui->comboBox->removeItem(0);
  }
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
  show();
}

void CharSelect::enter(){
  size_t id = ui->comboBox->currentData().toULongLong();
  loginConf.setVal("CHAR", ui->comboBox->currentIndex());
  if(runapp->getClient()->setChar(id)){
    entered();
  }else{
    logout();
  }
}

void CharSelect::logout(){
  delete runapp->getClient();
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
