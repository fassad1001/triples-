#include "OntologyDataBaseReader.h"

OntologyDataBaseReader::OntologyDataBaseReader(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

Ontology OntologyDataBaseReader::readOntology(const QString &ontologyName)
{
    //QSQLITE это имя подключения
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(getDataBaseName());
    //создаю БД
    sdb.open();
    if(sdb.isOpen())
    {
        //создаю запрос для подключения QSQLITE
        QSqlQuery my_query;
        //если открыта БД НЕуспешно
        if(!my_query.exec("SELECT subject_id, predicate_id, object_id FROM Triples"
                      " WHERE onotology_id = ("
                      " SELECT id FROM Names WHERE name = " + ontologyName +
                          " AND isClass = true)"
                      " );")
                && my_query.isActive())
        {

        }
    }
}

QStringList OntologyDataBaseReader::readOntologyName()
{

}
