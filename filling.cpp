#include "filling.h"
#include "ui_filling.h"
#include "QtSql"
#include <QTableView>
#include <QAbstractTableModel>
#include <QList>
#include <QMessageBox>

#include <QModelIndex>

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




void Filling::test() // ЭТО РАБОЧИЙ СЛОТ
{
    m_Per();                 // Пересоздать модель
    modelPersons->setFilter(QString("ID_Nomination = %1").arg(2)); //пробегаемся по всем номинациям
    modelPersons->select();  // обновить список клубов
}

void Filling::test2() // ЭТО ТЕСТОВОЙ СЛОТ
{
    QSqlQuery query;
    //int PersAge    = modelPersons->record(ui->tablePersons->currentIndex().row()).value("Age").toInt();
     query.exec("UPDATE Person SET ID_Nomination=2 WHERE ID_Nomination=1");
 //  modelPersons->select();
}



void Filling::on_pushButton_released()
{
    QSqlQuery query;
    query.exec("insert into Person (FIO, ID_Club, Sex, Age, ID_Nomination) values ('', 1, 1, 13, 1)");
    modelPersons->submitAll();
    modelPersons->select();
}

void Filling::on_pushButton_2_released()
{
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите удалить участника?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Discard);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
            modelPersons->removeRows(ui->tablePersons->currentIndex().row(), 1);
            modelPersons->select();
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }

}

void Filling::on_pushButton_3_released()
{
    QSqlQuery query;
    query.exec("insert into Club (Name) values ('')");
    modelPersons->submitAll();
    modelClub->submitAll();
    modelClub->select();
}

void Filling::on_pushButton_4_released()
{   
    int IDclub = ui->tableClubs->currentIndex().row();
    QMessageBox msgBox;
    msgBox.setText("Вы действительно хотите удалить этот клуб?");
    msgBox.setInformativeText("Все участники этого клуба будут удалены!");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Discard);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
                if (IDclub == 0) {
                    QMessageBox::warning(this, "Внимание","Это поле не подлежит удалению!");
                    } else
                        {
                        modelClub->removeRows(ui->tableClubs->currentIndex().row(), 1);
                        modelClub->select();
                        }
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}


//Свернуть их, что б не мешались
void Filling::m_Per()
{
    modelPersons = new QSqlRelationalTableModel(this);
    modelPersons->setTable("Person");
    modelPersons->setRelation(2, QSqlRelation("Club", "ID_Club", "Name"));
    modelPersons->setRelation(3, QSqlRelation("Sex", "ID_Sex", "Name"));
    modelPersons->setRelation(5, QSqlRelation("Nomination", "ID_Nomination", "Name"));
    modelPersons->setHeaderData(1, Qt::Horizontal, "ФИО");
    modelPersons->setHeaderData(2, Qt::Horizontal, "Клуб");
    modelPersons->setHeaderData(3, Qt::Horizontal, "Пол");
    modelPersons->setHeaderData(4, Qt::Horizontal, "Возраст");
    modelPersons->setHeaderData(5, Qt::Horizontal, "Номинация");

    ui->tablePersons->setModel(modelPersons);
    ui->tablePersons->setColumnHidden(0, true); // Скрываем колонку с id записей
    ui->tablePersons->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePersons->setSelectionMode(QAbstractItemView::SingleSelection); // выделение лишь одной строки в таблице
    ui->tablePersons->setItemDelegate(new QSqlRelationalDelegate(ui->tablePersons));
    ui->tablePersons->horizontalHeader()->setStretchLastSection(true);
    ui->tablePersons->resizeColumnsToContents(); // размер колонок по содержимому
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tablePersons->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    connect(ui->tablePersons->model(),&QAbstractItemModel::dataChanged,this, &Filling::test2); // поймать изменения - тирегрнуть слот test2 не факт что нужно!
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
    ui->tableClubs->horizontalHeader()->setStretchLastSection(true);
    ui->tableClubs->resizeColumnsToContents();

//  connect(ui->tableClubs->selectionModel(), SIGNAL(currentChanged(QModelIndex , QModelIndex)), this, SLOT(test()), Qt::DirectConnection); // поймать щелчки по форме - тирегрнуть слот test
    connect(ui->tableClubs->model(),&QAbstractItemModel::dataChanged,this, &Filling::test); // поймать изменения - тирегрнуть слот test
}

int Filling::autoNomination(int age,int id_Sex) //Пристрой эту штуку на добавление новой записи в таблицу участников
{                                               //а сможешь оптимизировать - честь и хвала тебе!!!)
    int nomination = 0;
    if (age >= 12 && age <= 13) nomination = 2;
          else if (age >= 14 && age <= 15) nomination = 3;
          else if (age >= 16 && age <= 17) nomination = 4;
          else if (age >= 18 && age <= 24) nomination = 5;
          else if (age >= 25 && age <= 34) nomination = 6;
          else if (age >= 35 && age <= 44) nomination = 7;
          else if (age >= 45) nomination = 8;
    if (id_Sex == 1) nomination += 8; //если пол женский, то ее номинации начинаются с 9
    return nomination;
}

void Filling::on_toGroupBtn_clicked()
{
    QMessageBox msgBox;

    QSqlQuery query;
    QModelIndex index;
    QVariant idPers = 0;
    int qntGroup = 0;
    int group = 1;
    //modelPersons = new QSqlRelationalTableModel(this);
    //modelPersons->setTable("Persons");
    for (int i = 2; i <= 15; i++)
    {
        group = 1;
        modelPersons->setFilter(QString("ID_Nomination = %1").arg(i)); //пробегаемся по всем номинациям
        modelPersons->setSort(2, Qt::AscendingOrder);                  //сортируем по клубам
        ui->tablePersons->setModel(modelPersons);

        if (modelPersons->rowCount() % 4 == 0)                         //считаем кол-во групп, при условии что в группе может быть не больеш 4 человек
            qntGroup = modelPersons->rowCount() / 4;
        else
            qntGroup = modelPersons->rowCount() / 3;

        for (int j = 0; j < modelPersons->rowCount(); j++, group++)
        {
            if (group == qntGroup) group = 1;                         //группа, в которую поместим человека
            ui->tablePersons->selectRow(j);
            index = ui->tablePersons->model()->index(j, 0, QModelIndex());
            idPers = ui->tablePersons->model()->data(index, Qt::DisplayRole);
            query.prepare("UPDATE Person SET Group = :Group WHERE ID_Person = :IdPerson");
            query.bindValue(":Group", group);
            query.bindValue(":IdPerson", idPers);
            if (!query.exec())
            {
                   msgBox.setText("Упс, в назачении группы произошла ошибка");
                   msgBox.exec();
            }
        }
    }
    test();
}
