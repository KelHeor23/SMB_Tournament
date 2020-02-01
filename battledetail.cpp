#include "battledetail.h"
#include "ui_battledetail.h"

BattleDetail::BattleDetail(QWidget *parent, int firstID, int secondID) :
    QDialog(parent),
    ui(new Ui::BattleDetail)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    paletteFirst.setColor(QPalette::Base, QColor(255,0,0, 50));
    paletteSecond.setColor(QPalette::Base, QColor(0,0,255, 50));

    firstPersID = firstID;
    firstPersName = db->getNamePerson(firstID);
    secondPersID = secondID;
    secondPersName = db->getNamePerson(secondID);

    ui->firstPersonName->setText(firstPersName);
    ui->firstPersonName->setPalette(paletteFirst);
    ui->secondPersonName->setText(secondPersName);
    ui->secondPersonName->setPalette(paletteSecond);
}

BattleDetail::~BattleDetail()
{
    delete ui;
}
