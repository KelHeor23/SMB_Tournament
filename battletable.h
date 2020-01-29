#ifndef BATTLETABLE_H
#define BATTLETABLE_H

#include <QDialog>

namespace Ui {
class BattleTable;
}

class BattleTable : public QDialog
{
    Q_OBJECT

public:
    explicit BattleTable(QWidget *parent = nullptr);
    ~BattleTable();

private:
    Ui::BattleTable *ui;
};

#endif // BATTLETABLE_H
