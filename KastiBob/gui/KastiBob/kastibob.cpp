#include "kastibob.h"
#include "ui_kastibob.h"

KastiBob::KastiBob(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KastiBob)
{
    ui->setupUi(this);
}

KastiBob::~KastiBob()
{
    delete ui;
}
