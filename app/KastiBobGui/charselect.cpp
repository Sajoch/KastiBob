#include <QtCore/QTimer>
#include "charselect.h"
#include "src/client.hpp"

extern Client* tclient;
extern QTimer *logic_loop;
void GoToLoginForm();
void GoToCharSelect();
void GoToGameWindow();

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, enter);
}

void CharSelect::load(){
  while(ui->comboBox->count()>0){
    ui->comboBox->removeItem(0);
  }
  tclient->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), id);
  });
}

void CharSelect::enter(){
  logic_loop->start(1);
  size_t id = ui->comboBox->currentData().toULongLong();
  if(tclient->setChar(id)){
    GoToGameWindow();
  }else{
    logout();
  }
}

void CharSelect::logout(){
  delete tclient;
  logic_loop->stop();
  GoToLoginForm();
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
