#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "healer.h"
#include "runemaker.h"
#include "hotheys.h"

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
    healer.setModal(false);
    healer.show();
    healer.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    Runemaker runemaker;
    runemaker.setModal(true);
    runemaker.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Hotheys hotkeys;
    hotkeys.setModal(true);
    hotkeys.exec();
}
