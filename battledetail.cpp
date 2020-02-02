#include "battledetail.h"
#include "ui_battledetail.h"

BattleDetail::BattleDetail(QWidget *parent, int idBattle, int firstID, int secondID) :
    QDialog(parent),
    ui(new Ui::BattleDetail)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    modelFirstRound = new QSqlTableModel(this);
    modelSecondRound = new QSqlTableModel(this);
    modelThirdRound = new QSqlTableModel(this);

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


    modelFirstRound->setTable("BattleDetail");
    modelFirstRound->setFilter(QString("[ID_Battle] = %1 and [Round] = 1").arg(idBattle));

    modelSecondRound->setTable("BattleDetail");
    modelSecondRound->setFilter(QString("[ID_Battle] = %1 and [Round] = 2").arg(idBattle));

    modelThirdRound->setTable("BattleDetail");
    modelThirdRound->setFilter(QString("[ID_Battle] = %1 and [Round] = 3").arg(idBattle));

    ui->tableFirstRound->setModel(modelFirstRound);
    ui->tableSecondRound->setModel(modelSecondRound);
    ui->tableThirdRound->setModel(modelThirdRound);


    ui->tableFirstRound->setColumnHidden(0, true);
    //ui->tableFirstRound->setColumnHidden(1, true);
    ui->tableFirstRound->setColumnHidden(2, true);

    ui->tableSecondRound->setColumnHidden(0, true);
    //ui->tableSecondRound->setColumnHidden(1, true);
    ui->tableSecondRound->setColumnHidden(2, true);

    ui->tableThirdRound->setColumnHidden(0, true);
    //ui->tableThirdRound->setColumnHidden(1, true);
    ui->tableThirdRound->setColumnHidden(2, true);



    setOptionsModel(modelFirstRound);
    setOptionsModel(modelSecondRound);
    setOptionsModel(modelThirdRound);



    /*modelFirstRound->select();
    modelSecondRound->select();
    modelThirdRound->select();*/
}

BattleDetail::~BattleDetail()
{
    delete ui;
}

void BattleDetail::setOptionsModel(QSqlTableModel *model)
{
    model->setHeaderData(3, Qt::Horizontal, "Сход 1");
    model->setHeaderData(4, Qt::Horizontal, "Сход 2");
    model->setHeaderData(5, Qt::Horizontal, "Сход 3");
    model->setHeaderData(6, Qt::Horizontal, "Сход 4");
    model->setHeaderData(7, Qt::Horizontal, "Сход 5");
    model->setHeaderData(8, Qt::Horizontal, "Сход 6");
    model->setHeaderData(9, Qt::Horizontal, "Сход 7");
    model->setHeaderData(10, Qt::Horizontal, "Сход 8");
    model->setHeaderData(11, Qt::Horizontal, "Сход 9");
    model->setHeaderData(12, Qt::Horizontal, "Сход 10");

    model->select();
}

void BattleDetail::calcTotalWins()
{
    firstTotalWin = 0;
    secondTotalWin = 0;

    calcWins(modelFirstRound, 1);
    calcWins(modelSecondRound, 2);
    calcWins(modelThirdRound, 3);

    firstTotalWin += firstPersR1 + firstPersR2 + firstPersR3;
    secondTotalWin += secondPersR1 + secondPersR2 + secondPersR3;
}

void BattleDetail::calcWins(QSqlTableModel *model, int round)
{
    QModelIndex indexFirst;
    QModelIndex indexSecond;
    int qntWinFirst = 0;
    int qntWinSecond = 0;

    for (int i = 0; i < 10; i++)
    {
        indexFirst = model->index(0, i + 3);
        indexSecond = model->index(1, i + 3);

        if (model->data(indexFirst).toInt() > model->data(indexSecond).toInt())
            qntWinFirst++;
        else if (model->data(indexFirst).toInt() < model->data(indexSecond).toInt())
            qntWinSecond++;
    }
    switch(round)
    {
    case 1:
        firstPersR1 = qntWinFirst;
        secondPersR1 = qntWinSecond;
        break;
    case 2:
        firstPersR2 = qntWinFirst;
        secondPersR2 = qntWinSecond;
        break;
    case 3:
        firstPersR3 = qntWinFirst;
        secondPersR3 = qntWinSecond;
        break;
    }
}

void BattleDetail::on_pushButton_released()
{
    calcTotalWins();

    ui->firstQntWins->setText(QString("Кол-во выйгранных сходов: %1").arg(firstTotalWin));
    ui->secondQntWins->setText(QString("Кол-во выйгранных сходов: %1").arg(secondTotalWin));
}
