#include "OntologyDataBaseWriter.h"

OntologyDataBaseWriter::OntologyDataBaseWriter(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{
}

void OntologyDataBaseWriter::writeOntology(const QString &ontologyName, const Ontology &ontology)
{
    remove(ontologyName);
    QHash<int, QString> ontologyNames = getOntologyNames();
    if(ontologyNames.key(ontologyName) == int())
    {
        insert_OntologyNames(QSet<QString>()<<ontologyName);
    }

    ontologyNames = getOntologyNames();
    QSet<QString> namesToInsert;
    const QSet<Triple> writingOntology = ontology.getStorage();
    QHash<int, QString> names;
    foreach(Triple triple, writingOntology)
    {
        if(names.key(triple.subject()) == int())
        {
            namesToInsert += triple.subject();
        }
        if(names.key(triple.predicate()) == int())
        {
            namesToInsert += triple.predicate();
        }
        if(names.key(triple.object()) == int())
        {
            namesToInsert += triple.object();
        }
    }
    insert_Names(namesToInsert);
    names = getNames();

    QSet<Triple> triplesOfIDs;
    const QString ontologyID = QString::number(ontologyNames.key(ontologyName));
    foreach(Triple triple, writingOntology)
    {
        const QString subjectID = QString::number(names.key(triple.subject()));
        const QString predicateID = QString::number(names.key(triple.predicate()));
        const QString objectID = QString::number(names.key(triple.object()));
        triplesOfIDs += Triple(subjectID, predicateID, objectID);
    }
    insert_Triples(ontologyID, triplesOfIDs);
}

void OntologyDataBaseWriter::remove(const QString &ontologyName)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());

    const QHash<int, QString> hash = getOntologyNames();

    myQuery.exec("BEGIN;");

    if(!hash.contains(hash.key(ontologyName)))
    {
        return;
    }
    //---------------------------------------------------------------------------------
    if(myQuery.prepare("DELETE "
                       "FROM Triples "
                       "WHERE ontology_id = :ontologyName;"))
    {
        const int ontologyID = hash.key(ontologyName);
        myQuery.bindValue(":ontologyName", ontologyID);
        myQuery.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
        return;
    }
    if(myQuery.prepare("DELETE "
                       "FROM ontologyNames "
                       "WHERE name = :ontologyName;"))
    {
        myQuery.bindValue(":ontologyName", ontologyName);
        myQuery.exec();
        myQuery.exec("END;");
        myQuery.exec("VACUUM;");
        return;
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
        return;
    }
}

void OntologyDataBaseWriter::insert_Names(const QSet<QString> &namesToInsert)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());
    myQuery.exec("BEGIN;");
    if(myQuery.prepare("INSERT "
                       "INTO Names "
                       "VALUES (null, :nameToInsert);"))
    {
        foreach(QString nameToInsert, namesToInsert)
        {
            myQuery.bindValue(":nameToInsert", nameToInsert);
            myQuery.exec();
        }
        myQuery.exec("END;");

        return;
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на добавление имени :"<<myQuery.lastError();
        return;
    }
    return;
}

void OntologyDataBaseWriter::insert_OntologyNames(const QSet<QString> &namesToInsert)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());

    myQuery.exec("BEGIN;");

    if(myQuery.prepare("INSERT "
                       "INTO ontologyNames "
                       "VALUES (null, :nameToInsert);"))
    {
        foreach(QString nameToInsert, namesToInsert)
        {
            myQuery.bindValue(":nameToInsert", nameToInsert);
            myQuery.exec();
        }

        myQuery.exec("END;");

        return;
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на добавление имени онтологии:"<<myQuery.lastError();
        return;
    }
    return;

}

void OntologyDataBaseWriter::insert_Triples(QString ontologyID, QSet<Triple> TripleIDs)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());

    myQuery.exec("BEGIN;");

    if(myQuery.prepare("INSERT "
                       "INTO Triples "
                       "VALUES (:ontology_id, :subject_id "
                       ", :predicate_id, :object_id);"))
    {
        foreach(Triple triple, TripleIDs)
        {
            myQuery.bindValue(":ontology_id", ontologyID);
            myQuery.bindValue(":subject_id", triple.subject());
            myQuery.bindValue(":predicate_id", triple.predicate());
            myQuery.bindValue(":object_id", triple.object());
            myQuery.exec();

        }


        myQuery.exec("END;");

        return;
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на добавление тройки:"<<myQuery.lastError();
        return;
    }
    //----------------------------------------------------------------------------------
    return;
}

Ontology OntologyDataBaseWriter::importFromCSV(const QString &fileName,
                                               const QString ontologyName,
                                               const QHash<QString, QString> SystemValueUserValue)
{
    //у меня есть файл
    //
    QSet<Triple> triples;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QSet<Triple>();
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList triplesLine = line.split(",");
        const QString subject = triplesLine.at(0);
        const QString userPredicate = triplesLine.at(1);
        QString systemPredicate;
        if(!SystemValueUserValue.key(userPredicate).isNull())
        {
            systemPredicate = SystemValueUserValue.key(userPredicate);
        }
        else
        {
            systemPredicate = userPredicate;
        }
        const QString object = triplesLine.at(2);
        triples += Triple(subject, systemPredicate, object);
    }
    file.close();
    const Ontology ontology = Ontology(triples);

    writeOntology(ontologyName, ontology);
    return ontology;
}
