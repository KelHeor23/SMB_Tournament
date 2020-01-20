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
    return a.exec();
}
