#include "OntologyDataBaseReader.h"

OntologyDataBaseReader::OntologyDataBaseReader(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

Ontology OntologyDataBaseReader::readOntology(const QString &ontologyName)
{
    const QHash<int, QString> itemsNames = getNames();
    const QHash<int, QString> ontologyNames = getOntologyNames();

    QSqlQuery my_query = getQuery(getDataBaseName());

    QSet<Triple> triples;

    if(my_query.prepare("SELECT * "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", ontologyNames.key(ontologyName));
        my_query.exec();
        qWarning()<<":ontologyName"<<ontologyNames.key(ontologyName);

        while(my_query.next())
        {
            const int subjectID = my_query.value("subject_id").toInt();
            const QString subject = itemsNames.value(subjectID);

            const int predicateID = my_query.value("predicate_id").toInt();
            const QString predicate = itemsNames.value(predicateID);

            const int objectID = my_query.value("object_id").toInt();
            const QString object = itemsNames.value(objectID);

            const int ontologyID = my_query.value("ontology_id").toInt();
            const QString ontology = ontologyNames.value(ontologyID);

            qWarning()<<"читаю"<<Triple(subject, predicate, object).toString();
            triples.insert(Triple(subject, predicate, object));
        }

    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    return Ontology(triples);
}
