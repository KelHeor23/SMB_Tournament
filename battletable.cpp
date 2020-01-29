#include "battletable.h"
#include "ui_battletable.h"

BattleTable::BattleTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BattleTable)
{
    ui->setupUi(this);
}

BattleTable::~BattleTable()
{
    delete ui;
}
