#include "TOntologyDataBaseWriter.h"

TOntologyDataBaseWriter::TOntologyDataBaseWriter()
{
}

void TOntologyDataBaseWriter::TestWriteOntology_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <Ontology> ("ontology");

    QTest::newRow("write-a-empty-ontology")
            << "empty-ontology1"
            << (Ontology(QSet<Triple>()));


    QTest::newRow("write-ontology")
            << "ontology1"
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")));
}

void TOntologyDataBaseWriter::TestWriteOntology()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TOntologyDataBaseWriter::TestWriteOntology.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }
    OntologyDataBaseWriter writer(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    OntologyDataBaseReader reader(dataBaseName);
    //если прочитал из БД то же что и записал то все правильно
    QCOMPARE(reader.readOntology(ontologyName), ontology);
}

void TOntologyDataBaseWriter::TestRemove_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <Ontology> ("ontology");

    //проверить удаление конкретной онтологии из множества, проверить удаление несуществующей онтологии
    QTest::newRow("DB-ontology-1")
            << "ontology1"
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")));

    QTest::newRow("DB-ontology-2")
            << "ontology2"
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class4", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class1", Ontology::CONTAINS, "class4")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")));
}

void TOntologyDataBaseWriter::TestRemove()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TOntologyDataBaseWriter::TestRemove.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    QHash<int, QString> ontologyNames1 = writer.getOntologyNames();
    QHash<int, QString> ontologyNames2 = writer.getOntologyNames();
    ontologyNames1.remove(ontologyNames2.key(ontologyName));
    const QHash<int, QString> compareHash = ontologyNames1;
    writer.remove(ontologyName);
    const QHash<int, QString> realHash = writer.getOntologyNames();
    QCOMPARE(compareHash, realHash);
}

void TOntologyDataBaseWriter::TestWriteOntologyName_data()
{
    QTest::addColumn <QString> ("ontologyName");

    QTest::newRow("non-existed-ontology")<<"Ontology1";

    QTest::newRow("existed-ontology")<<"Ontology2";
}

void TOntologyDataBaseWriter::TestWriteOntologyName()
{
    QFETCH(QString, ontologyName);

    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TOntologyDataBaseWriter::TestRemove.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.insert_OntologyNames(ontologyName);
    QCOMPARE(writer.isExists(ontologyName), true);
}
