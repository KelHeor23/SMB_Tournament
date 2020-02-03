#include "battledetail.h"
#include "ui_battledetail.h"

BattleDetail::BattleDetail(QWidget *parent, int idBattle, int firstID, int secondID) :
    QDialog(parent),
    ui(new Ui::BattleDetail)
{
    ui->setupUi(this);
    Parent = parent;

    db = new DataBase();
    db->connectToDataBase();

    modelFirstRound = new QSqlTableModel(this);
    modelSecondRound = new QSqlTableModel(this);
    modelThirdRound = new QSqlTableModel(this);

    paletteFirst.setColor(QPalette::Base, QColor(255,0,0, 50));
    paletteSecond.setColor(QPalette::Base, QColor(0,0,255, 50));

    IdBattle = idBattle;
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

    calcTotalWins();
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
    fitrstPersonPoints = 0;
    secondPersonPoints = 0;

    calcWins(modelFirstRound);
    calcWins(modelSecondRound);
    calcWins(modelThirdRound);

    ui->firstQntWins->setText(QString("Кол-во выйгранных сходов: %1").arg(firstTotalWin));
    ui->secondQntWins->setText(QString("Кол-во выйгранных сходов: %1").arg(secondTotalWin));
    ui->firstPersonPoints->setText(QString("Кол-во набранных очков: %1").arg(fitrstPersonPoints));
    ui->secondPersonPoints->setText(QString("Кол-во набранных очков: %1").arg(secondPersonPoints));
}

void BattleDetail::calcWins(QSqlTableModel *model)
{
    QModelIndex indexFirst;
    QModelIndex indexSecond;
    int first;
    int second;

    for (int i = 0; i < 10; i++)
    {
        indexFirst = model->index(0, i + 3);
        indexSecond = model->index(1, i + 3);

        first = model->data(indexFirst).toInt();
        second = model->data(indexSecond).toInt();
        if (first > second)
            firstTotalWin++;
        else if (model->data(indexFirst).toInt() < model->data(indexSecond).toInt())
            secondTotalWin++;

        fitrstPersonPoints += first;
        secondPersonPoints += second;
    }

}

void BattleDetail::on_pushButton_released()
{
    calcTotalWins();
}

void BattleDetail::on_pushButton_2_released()
{
    QSqlQuery query;
    int idWinner;
    (firstTotalWin > secondTotalWin) ? idWinner = firstPersID :
    (firstTotalWin < secondTotalWin) ? idWinner = secondPersID :
    (fitrstPersonPoints > secondPersonPoints) ? idWinner = firstPersID :
    (fitrstPersonPoints < secondPersonPoints) ? idWinner = secondPersID : idWinner = 0;

    query.prepare("update [Battles] set [ID_Winner] = :ID, [IsFinished] = 1 where [ID_Battle] = :ID_Battle");
    query.bindValue(":ID", idWinner);
    query.bindValue(":ID_Battle", IdBattle);
    if (!query.exec())
    {
        qDebug() << "DataBase: error of create ";
        qDebug() << query.lastError().text();
    }
    close();
}
