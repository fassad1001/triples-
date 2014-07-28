#include "OntologyDataBaseInterface.h"

OntologyDataBaseInterface::OntologyDataBaseInterface(const QString &dataBaseName) :
    dataBaseName_(dataBaseName)
{
    createTables();
}

void OntologyDataBaseInterface::createTables()
{
    //создаю запрос для подключения QSQLITE
    QSqlQuery my_query = getQuery(dataBaseName_);
    //если открыта БД НЕуспешно
    if(!my_query.exec("CREATE TABLE IF NOT EXISTS Names"
                      "("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name VARCHAR NOT NULL"
                      ");"))
    {
        qWarning()<<"Ошибка при создании таблицы Names:"<<my_query.lastError();
    }
    if(!my_query.exec("CREATE TABLE IF NOT EXISTS ontologyNames"
                      "("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name VARCHAR NOT NULL"
                      ");"))
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
                      ");"))
    {
        qWarning()<<"Ошибка при создании таблицы Triples:"<<my_query.lastError();
    }
}

QHash<int, QString> OntologyDataBaseInterface::getNames()
{
    QHash<int, QString> hash;
    QSqlQuery my_query = getQuery(getDataBaseName());
    if(my_query.exec("SELECT id, name "
                     "FROM Names;"))
    {
        qWarning()<<"=============================================";
        qWarning()<<"====";
        qWarning()<<"==";
        qWarning()<<"получаю хеш с именами:";
        while(my_query.next())
        {
            const int id = my_query.value("id").toInt();
            const QString name = my_query.value("name").toString();
            qWarning()<<id<<name;
            hash.insert(id, name);
        }
        qWarning()<<"хеш с именами получен!";
        qWarning()<<"==";
        qWarning()<<"====";
        qWarning()<<"=============================================";

    }
    return hash;
}

QHash<int, QString> OntologyDataBaseInterface::getOntologyNames()
{
    QHash<int, QString> hash;
    QSqlQuery my_query = getQuery(getDataBaseName());
    if(my_query.exec("SELECT id, name "
                     "FROM ontologyNames;"))
    {
            qWarning()<<"=============================================";
            qWarning()<<"====";
            qWarning()<<"==";
            qWarning()<<"получаю хеш с именамиОнтологий:";
            while(my_query.next())
            {
                const QVariant id = my_query.value("id");
                const QVariant name = my_query.value("name");
                qWarning()<<id<<name;
                hash.insert(id.toInt(), name.toString());
            }
            qWarning()<<"хеш с именамиОнтологий получен!";
            qWarning()<<"==";
            qWarning()<<"====";
            qWarning()<<"=============================================";
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
    QSqlQuery my_query = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(my_query.prepare("SELECT * "
                        "FROM ontologyNames "
                        "WHERE id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", hash.key(ontologyName));
        my_query.exec();

        if(my_query.first())
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
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
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
