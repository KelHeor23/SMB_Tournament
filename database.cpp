#include "database.h"


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
     db.close();
}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;

    if(!query.exec("CREATE TABLE [Person]("
                   "[ID_Person] INT PRIMARY KEY ON CONFLICT REPLACE NOT NULL,"
                   "[FIO] NVARCHAR(50),"
                   "[ID_Club] INT,"
                   "[Sex] INT,"
                   "[Age] INT)") ||
       !query.exec("CREATE TABLE [Club]("
                   "[ID_Club] INT PRIMARY KEY ON CONFLICT REPLACE,"
                   "[Name] NVARCHAR(50));") ||
       !query.exec("CREATE TABLE [Sex]("
                        "[ID_Sex] INT PRIMARY KEY ON CONFLICT REPLACE,"
                        "[Name] NVARCHAR(1));"))
    {
        qDebug() << "DataBase: error of create ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        //тестовые данные, перед релизом удалить
        query.exec("insert into Person (ID_Person, FIO, ID_Club, Sex, Age) values (1, 'Dasha', 1, 1, 1)");
        query.exec("insert into Club (ID_Club, Name) values (1, 'Excalibur')");
        query.exec("insert into Sex (ID_Sex, Name) values (1, 'Ж')");
        query.exec("insert into Sex (ID_Sex, Name) values (2, 'М')");
        return true;
    }
}
