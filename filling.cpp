#include "filling.h"
#include "ui_filling.h"
#include "QtSql"
#include <QTableView>
#include <QAbstractTableModel>
#include <QList>

Filling::Filling(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filling)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();    

    m_Per();
    modelPersons->select();
    modelPersons->setEditStrategy(QSqlTableModel::OnFieldChange);

    m_Club();
    modelClub->select();
    modelClub->setEditStrategy(QSqlTableModel::OnFieldChange);
}

Filling::~Filling()
{
    delete ui;
}

void Filling::on_pushButton_released()
{

    modelClub->insertRow(modelClub->rowCount(QModelIndex()));

    m_Per();                 // обновить список клубов
    modelPersons->select();  //

}

/* Удаление выбранной строки в tableView
model->removeRows(ui->modelPersons->currentIndex().row(), 1);
model->select();
P.s. надо бы все в одну кнопку, чтоб при нажатии на форму, он менял модель
*/



//Свернуть их, что б не мешались
void Filling::m_Per()
{
    modelPersons = new QSqlRelationalTableModel(this);
    modelPersons->setTable("Person");
    modelPersons->setRelation(2, QSqlRelation("Club", "ID_Club", "Name"));
    modelPersons->setRelation(3, QSqlRelation("Sex", "ID_Sex", "Name"));
    modelPersons->setHeaderData(1, Qt::Horizontal, "ФИО");
    modelPersons->setHeaderData(2, Qt::Horizontal, "Клуб");
    modelPersons->setHeaderData(3, Qt::Horizontal, "Пол");
    modelPersons->setHeaderData(4, Qt::Horizontal, "Возраст");

    ui->tablePersons->setModel(modelPersons);
    ui->tablePersons->setColumnHidden(0, true);    // Скрываем колонку с id записей
    ui->tablePersons->setSelectionBehavior(QAbstractItemView::SelectRows);
    // выделение лишь одно строки в таблице
    ui->tablePersons->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePersons->setItemDelegate(new QSqlRelationalDelegate(ui->tablePersons));
//  ui->tablePersons->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePersons->horizontalHeader()->setStretchLastSection(true);
    // размер колонок по содержимому
    ui->tablePersons->resizeColumnsToContents();
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

void Filling::m_Club()
{
    modelClub = new QSqlRelationalTableModel(this);
    modelClub->setTable("Club");
    modelClub->setHeaderData(1, Qt::Horizontal, "Название");

    ui->tableClubs->setModel(modelClub);
    ui->tableClubs->setColumnHidden(0, true);
    ui->tableClubs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableClubs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableClubs->setItemDelegate(new QSqlRelationalDelegate(ui->tableClubs));
//  ui->tableClubs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableClubs->horizontalHeader()->setStretchLastSection(true);
    ui->tableClubs->resizeColumnsToContents();
}
