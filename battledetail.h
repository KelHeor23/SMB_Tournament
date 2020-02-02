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

private:
    Ui::BattleDetail *ui;
    DataBase  *db;
    QPalette paletteFirst;
    QPalette paletteSecond;
    int firstPersID;
    QString firstPersName;
    int secondPersID;
    QString secondPersName;

    int firstPersR1 = 0;
    int firstPersR2 = 0;
    int firstPersR3 = 0;
    int secondPersR1 = 0;
    int secondPersR2 = 0;
    int secondPersR3 = 0;
    int firstTotalWin;
    int secondTotalWin;


    QSqlTableModel *modelFirstRound;
    QSqlTableModel *modelSecondRound;
    QSqlTableModel *modelThirdRound;

    void setOptionsModel(QSqlTableModel *model);
    void calcWins(QSqlTableModel *model, int);
    void calcTotalWins();
};

#endif // BATTLEDETAIL_H
