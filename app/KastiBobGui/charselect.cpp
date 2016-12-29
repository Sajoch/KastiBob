#include "charselect.h"
#include "ui_charselect.h"

CharSelect::CharSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharSelect)
{
    ui->setupUi(this);
}

CharSelect::~CharSelect()
{
    delete ui;
}
