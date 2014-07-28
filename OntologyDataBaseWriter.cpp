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
    QSqlQuery my_query = getQuery(getDataBaseName());
    const QHash<int, QString> hash = getOntologyNames();
    if(!hash.contains(hash.key(ontologyName)))
    {
        return;
    }
    //---------------------------------------------------------------------------------
    if(my_query.prepare("DELETE "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        const int ontologyID = hash.key(ontologyName);
        my_query.bindValue(":ontologyName", ontologyID);
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    if(my_query.prepare("DELETE "
                        "FROM ontologyNames "
                        "WHERE name = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", ontologyName);
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
}

QString OntologyDataBaseWriter::insert_Names(const QString &nameToInsert)
{
    QSqlQuery my_query = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(my_query.prepare("SELECT id "
                        "FROM Names "
                        "WHERE name = :nameToInsert;"))
    {
        my_query.bindValue(":nameToInsert", nameToInsert);
        my_query.exec();

        if(my_query.first())
        {
            while(my_query.next())
            {
                QString dbValue = my_query.value("id").toString();
                qWarning()<<"запись значения"<<nameToInsert<<"с айди"<<dbValue;
                return dbValue;
            }
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к имени в Names:"<<my_query.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        if(my_query.prepare("INSERT "
                            "INTO Names "
                            "VALUES (null, :nameToInsert);"))
        {
            my_query.bindValue(":nameToInsert", nameToInsert);
            my_query.exec();


            qWarning()<<"запись значения"<<nameToInsert<<"с айди"<<my_query.lastInsertId().toString();
            return my_query.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени :"<<my_query.lastError();
        }
        //----------------------------------------------------------------------------------

    }
    return QString();
}

QString OntologyDataBaseWriter::insert_OntologyNames(const QString &nameToInsert)
{
    QSqlQuery my_query = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(my_query.prepare("SELECT id "
                        "FROM ontologyNames "
                        "WHERE name = :nameToInsert;"))
    {
        my_query.bindValue(":nameToInsert", nameToInsert);
        my_query.exec();

        if(my_query.first())
        {
            while(my_query.next())
            {
                QString dbValue = my_query.value("id").toString();
                qWarning()<<"запись значенияОнтологии"<<nameToInsert<<"с айди"<<dbValue;
                return dbValue;
            }
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к имени онтологии в ontologyNames:"<<my_query.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        if(my_query.prepare("INSERT "
                            "INTO ontologyNames "
                            "VALUES (null, :nameToInsert);"))
        {
            my_query.bindValue(":nameToInsert", nameToInsert);
            my_query.exec();

            qWarning()<<"запись значенияОнтологии"<<nameToInsert<<"с айди"<<my_query.lastInsertId().toString();
            return my_query.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени онтологии:"<<my_query.lastError();
        }
        //----------------------------------------------------------------------------------

    }
    return QString();
}

QString OntologyDataBaseWriter::insert_Triples(const Triple &triple, const QString &ontologyName)
{
    QHash<int, QString> names = getNames();
    QHash<int, QString> ontologyNames = getOntologyNames();
    QSqlQuery my_query = getQuery(getDataBaseName());
    //---------------------------------------------------------------------------------
    if(my_query.prepare("SELECT * "
                        "FROM Triples "
                        "WHERE "
                        "subject_id = :subject "
                        "AND predicate_id = :predicate "
                        "AND object_id = :object "
                        "AND ontology_id = :ontology;"))
    {
        const int subjectID = names.key(triple.subject());
        my_query.bindValue(":subject", subjectID);

        const int predicateID = names.key(triple.predicate());
        my_query.bindValue(":predicate", predicateID);

        const int objectID = names.key(triple.object());
        my_query.bindValue(":object", objectID);

        const int ontologyID = ontologyNames.key(ontologyName);
        my_query.bindValue(":ontology", ontologyID);

        my_query.exec();

        if(my_query.first())
        {
            while(my_query.next())
            {
                const QVariant dbValue = my_query.value("line_id").toString();
                return dbValue.toString();
            }
        }
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на запрос к тройке:"<<my_query.lastError();
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        if(my_query.prepare("INSERT "
                            "INTO Triples "
                            "VALUES (null, :ontology_id, :subject_id"
                            ", :predicate_id, :object_id);"))
        {
            qWarning()<<"запись:"<<triple.toString();
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
            my_query.bindValue(":ontology_id", ontologyID);

            const int subjectID = names.key(triple.subject());
            my_query.bindValue(":subject_id", subjectID);

            const int predicateID = names.key(triple.predicate());
            my_query.bindValue(":predicate_id", predicateID);

            const int objectID = names.key(triple.object());
            my_query.bindValue(":object_id", objectID);

            qWarning()<<"subject"<<subjectID<<names.value(subjectID);
            qWarning()<<"predicate"<<predicateID<<names.value(predicateID);
            qWarning()<<"object"<<objectID<<names.value(objectID);

            my_query.exec();

            return my_query.lastInsertId().toString();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление тройки:"<<my_query.lastError();
        }
        //----------------------------------------------------------------------------------
    }
    return QString();
}
