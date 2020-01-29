#ifndef FILLING_H
#define FILLING_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "database.h"

namespace Ui {
class Filling;
}

class Filling : public QDialog
{
    Q_OBJECT

public:
    explicit Filling(QWidget *parent = nullptr);
    ~Filling();
    void m_Per();
    void m_Club();
    int autoNomination(int age, int id_Sex);

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void test();

    void test2();

    void on_toGroupBtn_clicked();

private:
    Ui::Filling *ui;

    DataBase        *db;
    QSqlRelationalTableModel *modelPersons;
    QSqlRelationalTableModel *modelClub;
};

#endif // FILLING_H
