#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME   "DemiDataBase"
#define DATABASE_NAME       "TournamentData.sqlite"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();
    //bool inserIntoTable(const QVariantList &data);
    void closeDataBase();
    QString getNamePerson(int);
    bool insertIntoBattlesDetail(int, int);

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    bool createTable();
};

#endif // DATABASE_H
