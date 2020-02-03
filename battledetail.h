#ifndef BATTLEDETAIL_H
#define BATTLEDETAIL_H

#include <QDialog>
#include "database.h"
#include <QSqlTableModel>

namespace Ui {
class BattleDetail;
}

class BattleDetail : public QDialog
{
    Q_OBJECT

public:
    explicit BattleDetail(QWidget *parent = nullptr, int = 0,int = 0, int = 0);
    ~BattleDetail();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::BattleDetail *ui;
    QWidget *Parent;
    DataBase  *db;
    QPalette paletteFirst;
    QPalette paletteSecond;
    int IdBattle;
    int firstPersID;
    QString firstPersName;
    int secondPersID;
    QString secondPersName;

    int firstTotalWin;
    int secondTotalWin;
    int fitrstPersonPoints;
    int secondPersonPoints;


    QSqlTableModel *modelFirstRound;
    QSqlTableModel *modelSecondRound;
    QSqlTableModel *modelThirdRound;

    void setOptionsModel(QSqlTableModel *model);
    void calcWins(QSqlTableModel *model);
    void calcTotalWins();
};

#endif // BATTLEDETAIL_H
