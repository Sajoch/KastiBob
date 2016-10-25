#include "runemaker.h"
#include "ui_runemaker.h"

Runemaker::Runemaker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Runemaker)
{
    ui->setupUi(this);
}

Runemaker::~Runemaker()
{
    delete ui;
}
