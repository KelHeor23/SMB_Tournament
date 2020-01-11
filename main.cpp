#include "mainwindow.h"
#include "QtSql"

#include <QApplication>
#include <QTableView>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ///a
    ///
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("TournamentData.sqlite");

    if (!sdb.open())
    {
       // qDebug() << "Что-то не так с соединением!";
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;
    }

    QSqlQuery query;

    query.exec("CREATE TABLE [Person]([FIO] NVARCHAR(50), [Club] INT, [Sex] INT, [Age] INT)");
    query.exec("insert into Person (FIO, Club, Sex, Age) values ('Dasha', 1, 1, 1)"); //Для проверок

    query.exec("CREATE TABLE [Club]([Name] NVARCHAR(50))");
    query.exec("insert into Club (Name) values ('Excalibur')"); //Для проверок



    QTableView view;
    QSqlTableModel model;

    model.setTable("Person");
    model.select();
    model.setEditStrategy(QSqlTableModel::OnRowChange);

    view.setModel(&model);
    view.show();


    return a.exec();
}
