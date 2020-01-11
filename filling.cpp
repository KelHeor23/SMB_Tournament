#include "filling.h"
#include "ui_filling.h"
#include "QtSql"

Filling::Filling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filling)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    model = new QSqlTableModel(this);
    model->setTable("Person");

    ui->tableView->setModel(model);

    model->select();
}

Filling::~Filling()
{
    delete ui;
}
