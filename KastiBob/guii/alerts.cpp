#include "alerts.h"
#include "ui_alerts.h"

Alerts::Alerts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alerts)
{
    ui->setupUi(this);
}

Alerts::~Alerts()
{
    delete ui;
}
