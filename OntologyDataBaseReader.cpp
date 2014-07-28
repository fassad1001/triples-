#include "OntologyDataBaseReader.h"

OntologyDataBaseReader::OntologyDataBaseReader(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

Ontology OntologyDataBaseReader::readOntology(const QString &ontologyName)
{
    const QHash<int, QString> itemsNames = getNames();
    const QHash<int, QString> ontologyNames = getOntologyNames();

    const QSqlQuery my_query = getQuery(getDataBaseName());

    QSet<Triple> triples;

    if(my_query.prepare("SELECT * "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", ontologyNames.key(ontologyName));
        my_query.exec();
        qWarning()<<":ontologyName"<<ontologyNames.key(ontologyName);

        if(my_query.first())
        {
            while(my_query.next())
            {
                const int subjectID = my_query.value("subject_id").toInt();
                const QString subject = itemsNames.value(subjectID);
                QVariant predicate_id = my_query.value("predicate_id");
                QVariant object_id = my_query.value("object_id");
                QVariant ontology_id = my_query.value("ontology_id");
                triples.insert(Triple(itemsNames.value(subject_id.toInt()), itemsNames.value(predicate_id.toInt()), itemsNames.value(object_id.toInt())));
            }
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }


    foreach(Triple tr, triples)
    {
        qWarning()<<"readOntology"<<tr.toString();
    }

    return Ontology(triples);
}
