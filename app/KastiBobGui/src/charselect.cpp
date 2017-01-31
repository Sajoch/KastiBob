#include "charselect.h"
#include "client.hpp"
#include "runmain.hpp"

extern RunMain* app;
extern Client* tclient;

//TODO shared loginConf between loginform and charselect

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent), 
    loginConf("login.cfg"){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  
  rChar = loginConf.getVal("CHAR", 0);
  
  connect(ui->pushButton, &QPushButton::clicked, this, &CharSelect::logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &CharSelect::enter);
  
  connect(this, &CharSelect::logouted, app, &RunMain::GoToLoginForm);
  connect(this, &CharSelect::entered, app, &RunMain::GoToGameWindow);
}

void CharSelect::load(){
  while(ui->comboBox->count()>0){
    ui->comboBox->removeItem(0);
  }
  tclient->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), (quint64)id);
  });
  ui->comboBox->setCurrentIndex(rChar);
  show();
}

void CharSelect::enter(){
  size_t id = ui->comboBox->currentData().toULongLong();
  loginConf.setVal("CHAR", ui->comboBox->currentIndex());
  if(tclient->setChar(id)){
    entered();
  }else{
    logout();
  }
}

void CharSelect::logout(){
  delete tclient;
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

}
