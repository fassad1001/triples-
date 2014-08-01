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
            triples.insert(Triple(subject, predicate, object));
        }

    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
    }
    return Ontology(triples);
}

void OntologyDataBaseReader::exportToCSV(const QString &fileName,
                                         const QString &ontologyName,
                                         const QHash<QString, QString> SystemValueUserValue)
{
    Ontology triples = readOntology(ontologyName);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    foreach(Triple triple, triples.getStorage())
    {
        const QString subject = triple.subject();
        const QString systemPredicate = triple.predicate();
        QString userPredicate;
        if(!SystemValueUserValue.value(systemPredicate).isNull())
        {
            userPredicate = SystemValueUserValue.value(systemPredicate);
        }
        else
        {
            userPredicate = systemPredicate;
        }
        const QString object = triple.object();
        out << subject + "," + userPredicate + "," + object + "\n";
    }
    file.close();
}
