#include "OntologyDataBaseInterface.h"

OntologyDataBaseInterface::OntologyDataBaseInterface(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
    createTables();
}

void OntologyDataBaseInterface::createTables()
{
    //создаю запрос для подключения QSQLITE
    QSqlQuery myQuery = getQuery(dataBaseName_);
    //если открыта БД НЕуспешно
    if(!myQuery.exec("CREATE TABLE IF NOT EXISTS Names"
                      "("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name VARCHAR NOT NULL"
                      ");"))
    {
        qWarning()<<"Ошибка при создании таблицы Names:"<<myQuery.lastError();
    }
    if(!myQuery.exec("CREATE TABLE IF NOT EXISTS ontologyNames"
                      "("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name VARCHAR NOT NULL"
                      ");"))
    {
        qWarning()<<"Ошибка при создании таблицы Names:"<<myQuery.lastError();
    }
    if(!myQuery.exec("CREATE TABLE IF NOT EXISTS Triples "
                      "("
                      "ontology_id INTEGER,"
                      "subject_id INTEGER NOT NULL,"
                      "predicate_id INTEGER NOT NULL,"
                      "object_id INTEGER NOT NULL,"
                      "PRIMARY KEY(ontology_id, subject_id, predicate_id,object_id)"
                      ");"))
    {
        qWarning()<<"Ошибка при создании таблицы Triples:"<<myQuery.lastError();
    }
}

QHash<int, QString> OntologyDataBaseInterface::getNames()
{
    QHash<int, QString> hash;
    QSqlQuery myQuery = getQuery(getDataBaseName());
    myQuery.exec("BEGIN;");
    if(myQuery.exec("SELECT id, name "
                     "FROM Names;"))
    {
        while(myQuery.next())
        {
            const int id = myQuery.value("id").toInt();
            const QString name = myQuery.value("name").toString();
            hash.insert(id, name);
        }
        myQuery.exec("END;");
    }
    return hash;
}

QHash<int, QString> OntologyDataBaseInterface::getOntologyNames()
{
    QHash<int, QString> hash;
    QSqlQuery myQuery = getQuery(getDataBaseName());
    if(myQuery.exec("SELECT id, name "
                     "FROM ontologyNames;"))
    {
            while(myQuery.next())
            {
                const QVariant id = myQuery.value("id");
                const QVariant name = myQuery.value("name");
                hash.insert(id.toInt(), name.toString());
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
    const QHash<int, QString> hash = getOntologyNames();
    QSqlQuery myQuery = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(myQuery.prepare("SELECT * "
                        "FROM ontologyNames "
                        "WHERE id = :ontologyName;"))
    {
        myQuery.bindValue(":ontologyName", hash.key(ontologyName));
        myQuery.exec();

        if(myQuery.first())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
    }
    return false;
}

QSet<QString> OntologyDataBaseInterface::getOntologys()
{
    QSet<QString> resultOntologys;
    QHash<int, QString> ontologys = getOntologyNames();
    foreach(QString ontology, ontologys.values())
    {
        resultOntologys += ontology;
    }
    return resultOntologys;
}

QSqlDatabase OntologyDataBaseInterface::getDataBase(const QString &fileName)
{
    QSqlDatabase db1 = QSqlDatabase::database();
    if(db1.isOpen())
    {
        //        qWarning()<<":) DB is opened adrealy! Use with care :)";
        return db1;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.isOpen())
    {

        qWarning()<<"i open DB for you :"<<db.open();
        QSqlQuery query(db);
        if(query.exec("PRAGMA count_changes = false;"))
        {
            qWarning()<<"Maximum PRAGMA ACTIVATED!";
        }

        if(!db.isOpen())
        {
            qWarning()<<"Error of opening DB:"<<db.lastError();
        }
        return db;
    }
    else
    {
        //        qWarning()<<"DB is opened adrealy! Use with care :)";
        return db;
    }
}

QSqlQuery OntologyDataBaseInterface::getQuery(const QString &fileName)
{
    return QSqlQuery(getDataBase(fileName));
}
