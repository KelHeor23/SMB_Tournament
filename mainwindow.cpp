#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (!filling)
        delete filling;
    if (!battleTable)
        delete battleTable;
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    filling = new Filling(this);
    filling->show();
}

void MainWindow::on_buttleTableBtn_released()
{
    battleTable = new BattleTable(this);
    battleTable->show();
}
