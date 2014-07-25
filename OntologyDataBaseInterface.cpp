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
                          ");")
                || !my_query.isActive())
        {
            qWarning()<<"Ошибка при создании таблицы Names:"<<my_query.lastError();
        }
        if(!my_query.exec("CREATE TABLE IF NOT EXISTS ontologyNames"
                          "("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "name VARCHAR NOT NULL"
                          ");")
                || !my_query.isActive())
        {
            qWarning()<<"Ошибка при создании таблицы Names:"<<my_query.lastError();
        }
        if(!my_query.exec("CREATE TABLE IF NOT EXISTS Triples "
                          "("
                          "line_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "ontology_id INTEGER,"
                          "subject_id INTEGER NOT NULL,"
                          "predicate_id INTEGER NOT NULL,"
                          "object_id INTEGER NOT NULL,"
                          "FOREIGN KEY(ontology_id) REFERENCES Names(id)"
                          ");")
                || !my_query.isActive())
        {
            qWarning()<<"Ошибка при создании таблицы Triples:"<<my_query.lastError();
        }
    }
    else
    {
        qWarning()<<"ошибка при открытии соединения :"<<sdb.lastError();
        qWarning()<<"isOpen"<<sdb.isOpen();
        qWarning()<<"isValid"<<sdb.isValid();
    }
}

QHash<int, QString> OntologyDataBaseInterface::getNames()
{
    QHash<int, QString> hash;
    QSqlQuery my_query;
    if(my_query.exec("SELECT id, name "
                     "FROM Names;"))
    {
        if(my_query.first())
        {
            do
            {
                QVariant id = my_query.value("id");
                QVariant name = my_query.value("name");
                hash.insert(id.toInt(), name.toString());
            }
            while(my_query.next());
        }
    }
    return hash;
}

QHash<int, QString> OntologyDataBaseInterface::getOntologyNames()
{
    QHash<int, QString> hash;
    QSqlQuery my_query;
    if(my_query.exec("SELECT id, name "
                     "FROM ontologyNames;"))
    {
        if(my_query.first())
        {
            do
            {
                QVariant id = my_query.value("id");
                QVariant name = my_query.value("name");
                hash.insert(id.toInt(), name.toString());
            }
            while(my_query.next());
        }
    }
    return hash;
}

QString OntologyDataBaseInterface::getDataBaseName()
{
    return dataBaseName_;
}

bool OntologyDataBaseInterface::isExists(const QString &ontologyName)
{
    //выполнить запрос на существование записей в которых айди равен айдишнику текстового поля из
    QHash<int, QString> hash = getOntologyNames();
    QSqlQuery my_query;
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(my_query.prepare("SELECT * "
                        "FROM ontologyNames "
                        "WHERE id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", hash.key(ontologyName));
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    if(!my_query.isActive())
    {
    }
    else
    {
        if(my_query.first())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //---------------------------------------------------------------------------------
    //Names
    return false;
}
