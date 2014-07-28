#include "OntologyDataBaseReader.h"

OntologyDataBaseReader::OntologyDataBaseReader(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

Ontology OntologyDataBaseReader::readOntology(const QString &ontologyName)
{
    const QHash<int, QString> itemsNames = getNames();
    const QHash<int, QString> ontologyNames = getOntologyNames();

    QSqlQuery myQuery = getQuery(getDataBaseName());

    QSet<Triple> triples;

    if(myQuery.prepare("SELECT * "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        myQuery.bindValue(":ontologyName", ontologyNames.key(ontologyName));
        myQuery.exec();
        qWarning()<<":ontologyName"<<ontologyNames.key(ontologyName);

        while(myQuery.next())
        {
            const int subjectID = myQuery.value("subject_id").toInt();
            const QString subject = itemsNames.value(subjectID);

            const int predicateID = myQuery.value("predicate_id").toInt();
            const QString predicate = itemsNames.value(predicateID);

            const int objectID = myQuery.value("object_id").toInt();
            const QString object = itemsNames.value(objectID);

            const int ontologyID = myQuery.value("ontology_id").toInt();
            const QString ontology = ontologyNames.value(ontologyID);

            qWarning()<<"читаю"<<Triple(subject, predicate, object).toString();
            triples.insert(Triple(subject, predicate, object));
        }

    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
    }
    return Ontology(triples);
}
