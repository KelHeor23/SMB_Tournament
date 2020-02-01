#ifndef BATTLETABLE_H
#define BATTLETABLE_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "database.h"

namespace Ui {
class BattleTable;
}

class BattleTable : public QDialog
{
    Q_OBJECT

public:
    explicit BattleTable(QWidget *parent = nullptr);
    ~BattleTable();

private slots:
    void on_pushButton_released();
    void BattleTable::insertInToBattlesTable(int idFirstPers, int idSecondPers);

private:
    Ui::BattleTable *ui;
   // QSqlRelationalTableModel *modelPersons;
    QSqlRelationalTableModel *modelBattles;
    DataBase *db;
};

#endif // BATTLETABLE_H
