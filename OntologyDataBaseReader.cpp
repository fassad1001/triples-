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

            triples.insert(Triple(subject, predicate, object));
        }

    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
    }
    return Ontology(triples);
}

void OntologyDataBaseReader::exportToCSV(const QString &fileName, const QString &ontologyName)
{
    //у меня есть имя онтологии
    //есть все тройки для этой онтологии
    //все тройки перебираю и отправляю в файл
    Ontology triples = readOntology(ontologyName);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    foreach(Triple triple, triples.getStorage())
    {
        out << triple.toString() + "\n";
    }
    // optional, as QFile destructor will already do it:
    file.close();
}
