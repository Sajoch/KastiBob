#include "charselect.h"

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent)
{
  ui = new Ui_CharSelect();
  ui->setupUi(this);
}

CharSelect::~CharSelect()
{

}
