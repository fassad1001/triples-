#include "OntologyDataBaseWriter.h"

OntologyDataBaseWriter::OntologyDataBaseWriter(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

void OntologyDataBaseWriter::writeOntology(const QString &ontologyName, const Ontology &ontology)
{
    remove(ontologyName);
    const QSet<Triple> writingOntology = ontology.getStorage();
    foreach(Triple triple, writingOntology)
    {
        insert_Triples(triple, ontologyName);
    }

}

void OntologyDataBaseWriter::remove(const QString &ontologyName)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());
    const QHash<int, QString> hash = getOntologyNames();
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
    }
    if(myQuery.prepare("DELETE "
                       "FROM ontologyNames "
                       "WHERE name = :ontologyName;"))
    {
        myQuery.bindValue(":ontologyName", ontologyName);
        myQuery.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<myQuery.lastError();
    }
}

QString OntologyDataBaseWriter::insert_Names(const QString &nameToInsert)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(myQuery.prepare("SELECT id "
                       "FROM Names "
                       "WHERE name = :nameToInsert;"))
    {
        myQuery.bindValue(":nameToInsert", nameToInsert);
        myQuery.exec();

        while(myQuery.next())
        {
            QString dbValue = myQuery.value("id").toString();
            return dbValue;
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к имени в Names:"<<myQuery.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!myQuery.first())
    {
        if(myQuery.prepare("INSERT "
                           "INTO Names "
                           "VALUES (null, :nameToInsert);"))
        {
            myQuery.bindValue(":nameToInsert", nameToInsert);
            myQuery.exec();


            return myQuery.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени :"<<myQuery.lastError();
        }
        //----------------------------------------------------------------------------------

    }
    return QString();
}

QString OntologyDataBaseWriter::insert_OntologyNames(const QString &nameToInsert)
{
    QSqlQuery myQuery = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(myQuery.prepare("SELECT id "
                       "FROM ontologyNames "
                       "WHERE name = :nameToInsert;"))
    {
        myQuery.bindValue(":nameToInsert", nameToInsert);
        myQuery.exec();

        if(myQuery.first())
        {
            while(myQuery.next())
            {
                QString dbValue = myQuery.value("id").toString();
                return dbValue;
            }
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к имени онтологии в ontologyNames:"<<myQuery.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!myQuery.first())
    {
        if(myQuery.prepare("INSERT "
                           "INTO ontologyNames "
                           "VALUES (null, :nameToInsert);"))
        {
            myQuery.bindValue(":nameToInsert", nameToInsert);
            myQuery.exec();

            return myQuery.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени онтологии:"<<myQuery.lastError();
        }
        //----------------------------------------------------------------------------------

    }
    return QString();
}

QString OntologyDataBaseWriter::insert_Triples(const Triple &triple, const QString &ontologyName)
{
    QHash<int, QString> names = getNames();
    QHash<int, QString> ontologyNames = getOntologyNames();
    QSqlQuery myQuery = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(myQuery.prepare("SELECT * "
                       "FROM Triples "
                       "WHERE "
                       "subject_id = :subject "
                       "AND predicate_id = :predicate "
                       "AND object_id = :object "
                       "AND ontology_id = :ontology;"))
    {
        const int subjectID = names.key(triple.subject());
        myQuery.bindValue(":subject", subjectID);

        const int predicateID = names.key(triple.predicate());
        myQuery.bindValue(":predicate", predicateID);

        const int objectID = names.key(triple.object());
        myQuery.bindValue(":object", objectID);

        const int ontologyID = ontologyNames.key(ontologyName);
        myQuery.bindValue(":ontology", ontologyID);

        myQuery.exec();

        while(myQuery.next())
        {
            const QVariant dbValue = myQuery.value("line_id").toString();
            return dbValue.toString();
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к тройке:"<<myQuery.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!myQuery.first())
    {
        if(myQuery.prepare("INSERT "
                           "INTO Triples "
                           "VALUES (null, :ontology_id, :subject_id"
                           ", :predicate_id, :object_id);"))
        {
            if(names.key(triple.subject()) == int())
            {
                insert_Names(triple.subject());
            }
            if(names.key(triple.predicate()) == int())
            {
                insert_Names(triple.predicate());
            }
            if(names.key(triple.object()) == int())
            {
                insert_Names(triple.object());
            }
            if(ontologyNames.key(ontologyName) == int())
            {
                insert_OntologyNames(ontologyName);
            }
            names = getNames();
            ontologyNames = getOntologyNames();

            const int ontologyID = ontologyNames.key(ontologyName);
            myQuery.bindValue(":ontology_id", ontologyID);

            const int subjectID = names.key(triple.subject());
            myQuery.bindValue(":subject_id", subjectID);

            const int predicateID = names.key(triple.predicate());
            myQuery.bindValue(":predicate_id", predicateID);

            const int objectID = names.key(triple.object());
            myQuery.bindValue(":object_id", objectID);

            myQuery.exec();

            return myQuery.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление тройки:"<<myQuery.lastError();
        }
        //----------------------------------------------------------------------------------
    }
    return QString();
}

Ontology OntologyDataBaseWriter::importFromCSV(const QString &fileName, const QString ontologyName)
{
    //у меня есть файл
    //
    QSet<Triple> triples;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return QSet<Triple>();
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList triplesLine = line.split(",");
        const QString subject = triplesLine.at(0);
        const QString predicate = triplesLine.at(1);
        const QString object = triplesLine.at(2);
        triples += Triple(subject, predicate, object);
    }
    file.close();
    const Ontology ontology = Ontology(triples);
    writeOntology(ontologyName, ontology);
    return ontology;
}
