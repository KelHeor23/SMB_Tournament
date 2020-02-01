#ifndef BATTLEDETAIL_H
#define BATTLEDETAIL_H

#include <QDialog>

namespace Ui {
class BattleDetail;
}

class BattleDetail : public QDialog
{
    Q_OBJECT

public:
    explicit BattleDetail(QWidget *parent = nullptr, int = 0, QString = "", int = 0, QString = "");
    ~BattleDetail();

private:
    Ui::BattleDetail *ui;
    QPalette paletteFirst;
    QPalette paletteSecond;
    int firstPersID;
    QString firstPersName;
    int secondPersID;
    QString secondPersName;
};

#endif // BATTLEDETAIL_H
