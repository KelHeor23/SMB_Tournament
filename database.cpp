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

    if(!query.exec("CREATE TABLE [Person]("                                     //Создание таблицы участников
                   "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "[FIO] NVARCHAR(50),"
                   "[ID_Club] INT,"
                   "[Sex] INT,"
                   "[Age] INT,"
                   "[Nomination] INT,"
                   "[Group] INT)") ||
       !query.exec("CREATE TABLE [Club]("                                      //Создание таблицы клубов
                   "ID_Club INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "[Name] NVARCHAR(50))") ||
       !query.exec("CREATE TABLE [Sex]("                                      //Создание таблицы гендеров :) (изменению не подлежит)
                   "[ID_Sex] INT PRIMARY KEY,"
                   "[Name] NVARCHAR(1))") ||
       !query.exec("CREATE TABLE [Nomination]("                              //Создание таблицы номинаций (изменению не подлежит)
                   "[ID_Nomination] INT PRIMARY KEY,"
                   "[Name] NVARCHAR(7))"))
    {
        qDebug() << "DataBase: error of create ";
        qDebug() << query.lastError().text();
        return false;
    } else {
        //тестовые данные, перед релизом удалить
        query.exec("insert into Person (ID, FIO, ID_Club, Sex, Age, Nomination) values (1, 'Dasha', 1, 1, 13, 1)");
        query.exec("insert into Club (ID_Club, Name) values (1, 'Не указан')");
        query.exec("insert into Sex (ID_Sex, Name) values (1, 'М')");  //не удалять константные значения
        query.exec("insert into Sex (ID_Sex, Name) values (2, 'Ж')");  //не удалять константные значения
        query.exec("insert into Nomination (ID_Nomination, Name) values"
                   "(1, 'Авто ввод'),"
                   "(2, '12-13 М'),"
                   "(3, '14-15 М'),"
                   "(4, '16-17 М'),"
                   "(5, '18-24 М'),"
                   "(6, '25-34 М'),"
                   "(7, '35-44 М'),"
                   "(8, '45+ М'),"
                   "(9, '12-13 Ж'),"
                   "(10, '14-15 Ж'),"
                   "(11, '16-17 Ж'),"
                   "(12, '18-24 Ж'),"
                   "(13, '25-34 Ж'),"
                   "(14, '35-44 Ж'),"
                   "(15, '45+ Ж')");  //Заполнение таблицы номинаций не удалять константные значения
        return true;
    }
}
