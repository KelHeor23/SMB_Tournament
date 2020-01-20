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

private slots:
    void on_pushButton_released();

private:
    Ui::Filling *ui;

    DataBase        *db;
    QSqlRelationalTableModel *modelPersons;
    QSqlRelationalTableModel *modelClub;
};

#endif // FILLING_H
