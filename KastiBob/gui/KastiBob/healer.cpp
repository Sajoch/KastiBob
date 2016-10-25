#include "healer.h"
#include "ui_healer.h"

Healer::Healer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Healer)
{
    ui->setupUi(this);
}

Healer::~Healer()
{
    delete ui;
}
