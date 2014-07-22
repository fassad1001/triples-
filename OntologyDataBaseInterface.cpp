#include "OntologyDataBaseInterface.h"

OntologyDataBaseInterface::OntologyDataBaseInterface(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
    createTables();
}

void OntologyDataBaseInterface::createTables()
{
    //QSQLITE это имя подключения
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(dataBaseName_);
    //создаю БД
    sdb.open();
    if(sdb.isOpen())
    {
        //создаю запрос для подключения QSQLITE
        QSqlQuery my_query;
        //если открыта БД НЕуспешно
        if(!my_query.exec("CREATE TABLE IF NOT EXISTS Names"
                          "("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "name VARCHAR NOT NULL"
                          "isClass BOOL"
                          ");")
                && my_query.isActive())
        {
            qWarning()<<"Ошибка при создании таблицы Names:"<<my_query.lastError();
        }
        if(!my_query.exec("CREATE TABLE IF NOT EXISTS Triples"
                          "("
                          "onotology_id INTEGER PRIMARY KEY,"
                          "subject_id INTEGER NOT NULL,"
                          "predicate_id INTEGER NOT NULL,"
                          "object_id INTEGER NOT NULL,"
                          "FOREIGN KEY(onotology_id) REFERENCES Names(id)"
                          ");")
                && my_query.isActive())
        {
            qWarning()<<"Ошибка при создании таблицы Triples:"<<my_query.lastError();
        }
        sdb.close();
    }
    else
    {
        qWarning()<<"ошибка при открытии соединения :"<<sdb.lastError();
        qWarning()<<"isOpen"<<sdb.isOpen();
        qWarning()<<"isValid"<<sdb.isValid();
    }
}

QString OntologyDataBaseInterface::getDataBaseName()
{
    return dataBaseName_;
}
