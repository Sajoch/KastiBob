#include "hotheys.h"
#include "ui_hotheys.h"

Hotheys::Hotheys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hotheys)
{
    ui->setupUi(this);
}

Hotheys::~Hotheys()
{
    delete ui;
}
