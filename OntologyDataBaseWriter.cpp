#include "OntologyDataBaseWriter.h"

OntologyDataBaseWriter::OntologyDataBaseWriter(const QString &dataBaseName) :
    OntologyDataBaseInterface(dataBaseName)
{

}

void OntologyDataBaseWriter::writeOntology(const QString &ontologyName, const Ontology &ontology)
{
    remove(ontologyName);
    QSet<Triple> writingOntology = ontology.getStorage();
    foreach(Triple triple, writingOntology)
    {
        insert_Triples(triple, ontologyName);
    }

}

void OntologyDataBaseWriter::remove(const QString &ontologyName)
{
    QHash<int, QString> hash = getOntologyNames();
    QSqlQuery my_query;
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(my_query.prepare("DELETE "
                        "FROM Triples "
                        "WHERE ontology_id = :ontologyName;"))
    {
        my_query.bindValue(":ontologyName", hash.key(ontologyName));
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
}

QString OntologyDataBaseWriter::insert_Names(const QString &nameToInsert)
{
    QSqlQuery my_query;
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(my_query.prepare("SELECT id "
                        "FROM Names "
                        "WHERE name = :nameToInsert;"))
    {
        my_query.bindValue(":nameToInsert", nameToInsert);
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    if(!my_query.isActive())
    {
    }
    else
    {
        if(my_query.first())
        {
            do
            {
                QVariant dbValue = my_query.value("id").toString();
                return dbValue.toString();
            }
            while(my_query.next());
        }
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        //добавить сабджект если он не существует
        if(my_query.prepare("INSERT "
                            "INTO Names "
                            "VALUES (null, :nameToInsert);"))
        {
            my_query.bindValue(":nameToInsert", nameToInsert);
            my_query.exec();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени онтологии:"<<my_query.lastError();
        }
        if(!my_query.isActive())
        {
            qWarning()<<"Ошибка при выполнениии запроса на добавление имени онтологии:"<<my_query.lastError();
        }
        else
        {
            return my_query.lastInsertId().toString();
        }
        //----------------------------------------------------------------------------------

    }
}

QString OntologyDataBaseWriter::insert_OntologyNames(const QString &nameToInsert)
{
    QSqlQuery my_query;
    //---------------------------------------------------------------------------------
    //удалить predicate если не существует
    if(my_query.prepare("SELECT id "
                        "FROM ontologyNames "
                        "WHERE name = :nameToInsert;"))
    {
        my_query.bindValue(":nameToInsert", nameToInsert);
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    if(!my_query.isActive())
    {
    }
    else
    {
        if(my_query.first())
        {
            do
            {
                QVariant dbValue = my_query.value("id").toString();
                return dbValue.toString();
            }
            while(my_query.next());
        }
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        //добавить сабджект если он не существует
        if(my_query.prepare("INSERT "
                            "INTO ontologyNames "
                            "VALUES (null, :nameToInsert);"))
        {
            my_query.bindValue(":nameToInsert", nameToInsert);
            my_query.exec();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление имени онтологии:"<<my_query.lastError();
        }
        if(!my_query.isActive())
        {
            qWarning()<<"Ошибка при выполнениии запроса на добавление имени онтологии:"<<my_query.lastError();
        }
        else
        {
            return my_query.lastInsertId().toString();
        }
        //----------------------------------------------------------------------------------

    }
}

QString OntologyDataBaseWriter::insert_Triples(const Triple &triple, const QString &ontologyName)
{
    QHash<int, QString> names = getNames();
    QHash<int, QString> ontologyNames = getOntologyNames();
    QSqlQuery my_query;
    //---------------------------------------------------------------------------------
    //вернуть значение существующего если получится
    if(my_query.prepare("SELECT line_id "
                        "FROM Triples "
                        "WHERE "
                        "subject_id = :subject "
                        "AND predicate_id = :predicate "
                        "AND object_id = :object "
                        "AND ontology_id = :onontology;"))
    {
        my_query.bindValue(":subject", names.key(triple.subject()));
        my_query.bindValue(":predicate", names.key(triple.predicate()));
        my_query.bindValue(":object", names.key(triple.object()));
        my_query.bindValue(":onontology", names.key(ontologyName));
        my_query.exec();
    }
    else
    {
        qWarning()<<"Ошибка при подготовке запроса на удаление имени в Names:"<<my_query.lastError();
    }
    if(!my_query.isActive())
    {
    }
    else
    {
        if(my_query.first())
        {
            do
            {
                QVariant dbValue = my_query.value("line_id").toString();
                return dbValue.toString();
            }
            while(my_query.next());
        }
    }
    //---------------------------------------------------------------------------------
    if(!my_query.first())
    {
        //добавить тройку
        if(my_query.prepare("INSERT "
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
            if(names.key(ontologyName) == int())
            {
                insert_OntologyNames(ontologyName);
            }
            names = getNames();
            my_query.bindValue(":ontology_id", ontologyNames.key(ontologyName));
            my_query.bindValue(":subject_id", names.key(triple.subject()));
            my_query.bindValue(":predicate_id", names.key(triple.predicate()));
            my_query.bindValue(":object_id", names.key(triple.object()));
            my_query.exec();
        }
        else
        {
            qWarning()<<"Ошибка при подготовке запроса на добавление тройки:"<<my_query.lastError();
        }
        if(!my_query.isActive())
        {
            qWarning()<<"Ошибка при выполнениии запроса на добавление тройки:"<<my_query.lastError();
        }
        else
        {
            return my_query.lastInsertId().toString();
        }
        //----------------------------------------------------------------------------------

    }
}
