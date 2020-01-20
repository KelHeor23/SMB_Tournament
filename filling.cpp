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

    modelPersons = new QSqlRelationalTableModel(this);
    modelPersons->setTable("Person");
    modelPersons->setRelation(2, QSqlRelation("Club", "ID_Club", "Name"));
    modelPersons->setRelation(3, QSqlRelation("Sex", "ID_Sex", "Name"));

    modelPersons->setHeaderData(1, Qt::Horizontal, "ФИО");
    modelPersons->setHeaderData(2, Qt::Horizontal, "Клуб");
    modelPersons->setHeaderData(3, Qt::Horizontal, "Пол");
    modelPersons->setHeaderData(4, Qt::Horizontal, "Возраст");

    modelClub = new QSqlRelationalTableModel(this);
    modelClub->setTable("Club");
    modelClub->setHeaderData(1, Qt::Horizontal, "Название");

    ui->tablePersons->setModel(modelPersons);     // Устанавливаем модель на TableView
//    ui->tablePersons->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tablePersons->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tablePersons->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePersons->setItemDelegate(new QSqlRelationalDelegate(ui->tablePersons));
   // ui->tablePersons->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePersons->horizontalHeader()->setStretchLastSection(true);
    // Устанавливаем размер колонок по содержимому
    ui->tablePersons->resizeColumnsToContents();
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tableClubs->setModel(modelClub);     // Устанавливаем модель на TableView
 //   ui->tableClubs->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableClubs->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableClubs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableClubs->setItemDelegate(new QSqlRelationalDelegate(ui->tableClubs));
   // ui->tableClubs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableClubs->horizontalHeader()->setStretchLastSection(true);
    // Устанавливаем размер колонок по содержимому
    ui->tableClubs->resizeColumnsToContents();

    modelPersons->select();
    modelPersons->setEditStrategy(QSqlTableModel::OnFieldChange);



    modelClub->select();
    modelClub->setEditStrategy(QSqlTableModel::OnRowChange);



}

Filling::~Filling()
{
    delete ui;
}

void Filling::on_pushButton_released()
{

    QSqlQuery query;
            query.exec("insert into Club (ID_Club) values ('')");
            modelClub->select();
            while(modelClub->canFetchMore())
            {
              modelPersons->fetchMore();
            }
    modelPersons->setRelation(2, QSqlRelation("Club", "ID_Club", "Name"));

}
