#include "OntologyDataBaseInterface.h"

OntologyDataBaseInterface::OntologyDataBaseInterface(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
    createTables();
}

void OntologyDataBaseInterface::createTables()
{
    //QSQLITE это имя подключения

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "def");
//    db.setDatabaseName(dataBaseName_);
//    //открываю БД
//    if(!db.open())
//    {
//        qWarning()<<"ошибка открытия соединения для "<<Q_FUNC_INFO<<db.lastError();
//        return;
//    }

    //создаю запрос для подключения QSQLITE
    QSqlQuery my_query = getQuery(dataBaseName_);
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

QHash<int, QString> OntologyDataBaseInterface::getNames()
{
//    QSqlDatabase db = QSqlDatabase::database("def");
//    if(!db.isOpen())
//    {
//        qWarning()<<"ошибка открытия соединения для "<<Q_FUNC_INFO<<db.lastError();
//        return QHash<int, QString>();
//    }
    QHash<int, QString> hash;
    QSqlQuery my_query = getQuery(getDataBaseName());
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
//    QSqlDatabase db = QSqlDatabase::database("def");
//    if(!db.isOpen())
//    {
//        qWarning()<<"ошибка открытия соединения для "<<Q_FUNC_INFO<<db.lastError();
//        return QHash<int, QString>();
//    }
    QHash<int, QString> hash;
    QSqlQuery my_query = getQuery(getDataBaseName());
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
//    QSqlDatabase db = QSqlDatabase::database("def");
//    if(!db.isOpen())
//    {
//        qWarning()<<"ошибка открытия соединения для "<<Q_FUNC_INFO<<db.lastError();
//        return false;
//    }
    //выполнить запрос на существование записей в которых айди равен айдишнику текстового поля из
    QHash<int, QString> hash = getOntologyNames();
    QSqlQuery my_query = getQuery(getDataBaseName());
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

QSqlDatabase OntologyDataBaseInterface::getDataBase(const QString &fileName)
{
    QSqlDatabase db1 = QSqlDatabase::database();
    if(db1.isOpen())
    {
        qWarning()<<":) DB is opened adrealy! Use with care :)";
        return db1;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.isOpen())
    {
        qWarning()<<"i open DB for you :"<<db.open();
        if(!db.isOpen())
        {
            qWarning()<<"Error of opening DB:"<<db.lastError();
        }
        return db;
    }
    else
    {
        qWarning()<<"DB is opened adrealy! Use with care :)";
        return db;
    }
}

QSqlQuery OntologyDataBaseInterface::getQuery(const QString &fileName)
{
    return QSqlQuery(getDataBase(fileName));
}
