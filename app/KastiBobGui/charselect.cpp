#include "charselect.h"
#include "gamewindow.h"
#include "loginform.h"
#include "src/client.hpp"

extern Client* tclient;
extern QTimer *logic_loop;

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent){
  ui = new Ui_CharSelect();
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, logout);
  connect(ui->pushButton_2, &QPushButton::clicked, this, enter);
  tclient->listChars([&](std::string name, size_t id){
    ui->comboBox->addItem(name.c_str(), id);
  });
}

void CharSelect::enter(){
  size_t id = ui->comboBox->currentData().toULongLong();
  if(tclient->setChar(id)){
    GameWindow* tmp = new GameWindow();
    delete this;
    tmp->show();
  }else{
    logout();
  }
}

void CharSelect::logout(){
  LoginForm* tmp = new LoginForm();
  delete this;
  tmp->show();
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
