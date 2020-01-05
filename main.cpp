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

    QTableView view;
    QSqlTableModel model;

    model.setTable("Person");
    model.select();
    model.setEditStrategy(QSqlTableModel::OnRowChange);

    view.setModel(&model);
    view.show();

    return a.exec();
}
