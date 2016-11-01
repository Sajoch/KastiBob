#include "cavebot.h"
#include "ui_cavebot.h"

Cavebot::Cavebot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cavebot)
{
    ui->setupUi(this);
}

Cavebot::~Cavebot()
{
    delete ui;
}
