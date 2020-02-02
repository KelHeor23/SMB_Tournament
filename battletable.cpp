#include "battletable.h"
#include "ui_battletable.h"
#include <QMessageBox>
#include <string>

BattleTable::BattleTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BattleTable)
{
    ui->setupUi(this);
    db = new DataBase();
    db->connectToDataBase();

    modelBattles = new QSqlRelationalTableModel(this);
    modelBattles->setTable("Battles");

    modelBattlesTwo = new QSqlRelationalTableModel(this); //Это пиздец, мне стдыно, придумай как избежать этого
    modelBattlesTwo->setTable("Battles");

    modelBattles->setHeaderData(1, Qt::Horizontal, "Первый боец");
    modelBattles->setHeaderData(2, Qt::Horizontal, "Второй боец");
    modelBattles->setRelation(1, QSqlRelation("Person", "ID", "FIO"));
    modelBattles->setRelation(2, QSqlRelation("Person", "ID", "FIO"));

    ui->tableBattles->setModel(modelBattles);
    ui->tableBattles->setColumnHidden(0, true);
    ui->tableBattles->setColumnHidden(3, true);

    modelBattlesTwo->select();
    modelBattles->select();

}

BattleTable::~BattleTable()
{
    delete battleDetail;
    delete ui;
}

int BattleTable::insertInToBattlesTable(int idFirstPers, int idSecondPers)
{
    QSqlQuery query;
    query.prepare("insert into Battles ([ID_First_Person], [ID_Second_Person], [IsFinished]) values (:ID_First_Person, :ID_Second_Person, 0)");
    query.bindValue(":ID_First_Person", idFirstPers);
    query.bindValue(":ID_Second_Person", idSecondPers);
    if (!query.exec())
    {
        qDebug() << "DataBase: error of create ";
        qDebug() << query.lastError().text();
    }
    return query.lastInsertId().toInt();
}

void BattleTable::on_pushButton_released()
{
    QSqlQuery query;
    QSqlQuery queryGetPersons;
    QList <int> persons;
    int group;
    int idFirstPers = 0;
    int idSecondPers = 0;
    int battleId = 0;
    query.exec("delete from Battles");
    query.exec("delete from BattleDetail");
    for (int i = 2; i <= 15; i++)
    {
        query.prepare("select distinct [Group] from Person where Nomination = :Nomination");  //Сначала получаю все группы, которые писутствую в номинации
        query.bindValue(":Nomination", i);
        query.exec();
        while (query.next())
        {
            persons.clear();
            queryGetPersons.prepare("select distinct ID from Person where [Nomination] = :Nomination and [Group] = :Group"); //нахожу всех участников в группе
            queryGetPersons.bindValue(":Nomination", i);
            queryGetPersons.bindValue(":Group", query.value(0).toInt());
            queryGetPersons.exec();

            while(queryGetPersons.next())
            {
                group = queryGetPersons.value(0).toInt();
                persons.append(group);    //запихуиваю участников в список, с ним проще работать
            }

            for (int j = 0; j < persons.length(); j++)
            {
                idFirstPers = persons[j];
                for (int k = j + 1; k < persons.length(); k++)
                {
                    idSecondPers = persons[k];
                    battleId = insertInToBattlesTable(idFirstPers, idSecondPers);
                }

                db->insertIntoBattlesDetail(battleId, idFirstPers);
                db->insertIntoBattlesDetail(battleId, idSecondPers);
            }            
        }
    }
}

void BattleTable::on_tableBattles_doubleClicked(const QModelIndex &index)
{
    int idBattle = modelBattlesTwo->data(modelBattles->index(ui->tableBattles->currentIndex().row(),0)).toInt();
    int idFirstPerson = modelBattlesTwo->data(modelBattles->index(ui->tableBattles->currentIndex().row(),1)).toInt();
    int idSecondPerson = modelBattlesTwo->data(modelBattles->index(ui->tableBattles->currentIndex().row(),2)).toInt();

    battleDetail = new BattleDetail(this, idBattle, idFirstPerson, idSecondPerson);
    battleDetail->show();
}
