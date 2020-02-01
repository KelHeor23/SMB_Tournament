#ifndef BATTLETABLE_H
#define BATTLETABLE_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "database.h"
#include "battledetail.h"

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
    int insertInToBattlesTable(int idFirstPers, int idSecondPers);
    void on_tableBattles_doubleClicked(const QModelIndex &index);

private:
    Ui::BattleTable *ui;
    BattleDetail *battleDetail;
    QSqlRelationalTableModel *modelBattles;
    QSqlRelationalTableModel *modelBattlesTwo; //стыд
    DataBase *db;
};

#endif // BATTLETABLE_H
