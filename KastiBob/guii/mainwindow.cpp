#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alerts.h"
#include "cavebot.h"
#include "healer.h"
#include "trainer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Healer healer;
    healer.setModal(true);
    healer.exec();
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{
    Cavebot cavebot;
    cavebot.setModal(true);
    cavebot.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    Trainer trainer;
    trainer.setModal(true);
    trainer.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    Alerts alerts;
    alerts.setModal(true);
    alerts.exec();
}

void MainWindow::on_pushButton_6_clicked()
{

}


