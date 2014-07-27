#include "OntologyDataBaseReader.h"

OntologyDataBaseReader::OntologyDataBaseReader(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

Ontology OntologyDataBaseReader::readOntology(const QString &ontologyName)
{
    QHash<int, QString> itemsNames = getNames();
    QHash<int, QString> ontologyNames = getOntologyNames();
    QSet<Triple> triples;
    QSqlQuery my_query = getQuery(getDataBaseName());

    if(my_query.prepare("SELECT * "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", ontologyNames.key(ontologyName));
        my_query.exec();
        qWarning()<<":ontologyName"<<ontologyNames.key(ontologyName);
        qWarning()<<my_query.lastError();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }

    if(my_query.isActive())
    {
        if(my_query.first())
        {
            do
            {
                QVariant subject_id = my_query.value("subject_id");
                QVariant predicate_id = my_query.value("predicate_id");
                QVariant object_id = my_query.value("object_id");
                QVariant ontology_id = my_query.value("ontology_id");
                triples.insert(Triple(itemsNames.value(subject_id.toInt()), itemsNames.value(predicate_id.toInt()), itemsNames.value(object_id.toInt())));
            }
            while(my_query.next());
        }
    }
    foreach(Triple tr, triples)
    {
        qWarning()<<"readOntology"<<tr.toString();
    }

    return Ontology(triples);
}
