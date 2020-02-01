#include "battledetail.h"
#include "ui_battledetail.h"

BattleDetail::BattleDetail(QWidget *parent, int firstID, QString firstName, int secondID, QString secondName) :
    QDialog(parent),
    ui(new Ui::BattleDetail)
{
    ui->setupUi(this);

    paletteFirst.setColor(QPalette::Base, QColor(255,0,0, 50));
    paletteSecond.setColor(QPalette::Base, QColor(0,0,255, 50));

    firstPersID = firstID;
    firstPersName = firstName;
    secondPersID = secondID;
    secondPersName = secondName;

    ui->firstPersonName->setText(firstPersName);
    ui->firstPersonName->setPalette(paletteFirst);
    ui->secondPersonName->setText(secondPersName);
    ui->secondPersonName->setPalette(paletteSecond);
}

BattleDetail::~BattleDetail()
{
    delete ui;
}
