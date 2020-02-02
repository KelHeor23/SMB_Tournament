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

private:
    Ui::BattleDetail *ui;
    DataBase  *db;
    QPalette paletteFirst;
    QPalette paletteSecond;
    int firstPersID;
    QString firstPersName;
    int secondPersID;
    QString secondPersName;
    QSqlTableModel *modelFirstRound;
    QSqlTableModel *modelSecondRound;
    QSqlTableModel *modelThirdRound;

    void setOptionsModel(QSqlTableModel *model);
};

#endif // BATTLEDETAIL_H
