#include "filling.h"
#include "ui_filling.h"

Filling::Filling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filling)
{
    ui->setupUi(this);
}

Filling::~Filling()
{
    delete ui;
}
