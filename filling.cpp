#include "filling.h"
#include "ui_filling.h"
#include "QtSql"

Filling::Filling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filling)
{
    ui->setupUi(this);

    //QTableView view;
    /*QSqlTableModel model;

    model.setTable("Person");
    model.select();
    model.setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->tableView->setModel(&model);
    ui->tableView->show();*/
}

Filling::~Filling()
{
    delete ui;
}
