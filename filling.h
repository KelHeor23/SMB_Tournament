#ifndef FILLING_H
#define FILLING_H

#include <QDialog>
#include <QSqlTableModel>
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

private:
    Ui::Filling *ui;

    DataBase        *db;
    QSqlTableModel  *model;
};

#endif // FILLING_H
