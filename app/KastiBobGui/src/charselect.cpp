#include <QtCore/QTimer>
#include "charselect.h"
#include "client.hpp"

extern Client* tclient;

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &CharSelect::logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, &CharSelect::enter);
}

void CharSelect::load(){
  while(ui->comboBox->count()>0){
    ui->comboBox->removeItem(0);
  }
  tclient->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), (quint64)id);
  });
}

void CharSelect::enter(){
  size_t id = ui->comboBox->currentData().toULongLong();
  if(tclient->setChar(id)){
    //GoToGameWindow();
  }else{
    logout();
  }
}

void CharSelect::logout(){
  delete tclient;
  //GoToLoginForm();
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
