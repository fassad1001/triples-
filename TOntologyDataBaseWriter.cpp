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
    const QString dataBaseName = dataTag + "TestWriteOntology.db";

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
    Ontology resultOntology = reader.readOntology(ontologyName);

    foreach(Triple triple, resultOntology.getStorage())
    {
        qWarning()<<"изначально:"<<ontologyName<<triple.toString();
    }

    //если прочитал из БД то же что и записал то все правильно
    QCOMPARE(reader.readOntology(ontologyName), ontology);
}

void TOntologyDataBaseWriter::TestReWriteOntology_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <Ontology> ("defaultOntology");


    QTest::newRow("full-empty-ontology")
            << "ontology1"
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")))
               << (Ontology(QSet<Triple>()));

    QTest::newRow("empty-full-ontology")
            << "ontology1"
            << (Ontology(QSet<Triple>()))
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")));

    QTest::newRow("full-full-ontology")
            << "ontology1"
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")))
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

void TOntologyDataBaseWriter::TestReWriteOntology()
{
    QFETCH(Ontology, defaultOntology);
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);

    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TestWriteOntology.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    OntologyDataBaseWriter writer(dataBaseName);

    writer.writeOntology(ontologyName, defaultOntology);
    writer.writeOntology(ontologyName, ontology);

    OntologyDataBaseReader reader(dataBaseName);
    Ontology resultOntology = reader.readOntology(ontologyName);

    QCOMPARE(reader.readOntology(ontologyName), ontology);
}

void TOntologyDataBaseWriter::TestRemove_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <QStringList> ("ontologyNames");
    QTest::addColumn <QList<Ontology> > ("ontology");

    //проверить удаление конкретной онтологии из множества, проверить удаление несуществующей онтологии
    QTest::newRow("DB-ontology-1")
            << "ontology3"
            << (QStringList()
                <<"ontology1"
                <<"ontology2")
            << (QList<Ontology>()<<(Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class4", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class1", Ontology::CONTAINS, "class4")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")))
               <<(Ontology(QSet<Triple>()
                           <<Triple("class1", Ontology::IS, Ontology::CLASS)
                           <<Triple("class2", Ontology::IS, Ontology::CLASS)
                           <<Triple("class3", Ontology::IS, Ontology::CLASS)
                           <<Triple("class1", Ontology::CONTAINS, "class2")
                           <<Triple("class2", Ontology::CONTAINS, "class3")
                           <<Triple("instance1", Ontology::IS, "class2"))));

    QTest::newRow("DB-ontology-2")
            << "ontology1"
            << (QStringList()
                <<"ontology1"
                <<"ontology2")
            << (QList<Ontology>()<<(Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class4", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::CONTAINS, "class2")
                         <<Triple("class1", Ontology::CONTAINS, "class4")
                         <<Triple("class2", Ontology::CONTAINS, "class3")
                         <<Triple("instance1", Ontology::IS, "class2")))
               <<(Ontology(QSet<Triple>()
                           <<Triple("class1", Ontology::IS, Ontology::CLASS)
                           <<Triple("class2", Ontology::IS, Ontology::CLASS)
                           <<Triple("class3", Ontology::IS, Ontology::CLASS)
                           <<Triple("class1", Ontology::CONTAINS, "class2")
                           <<Triple("class2", Ontology::CONTAINS, "class3")
                           <<Triple("instance1", Ontology::IS, "class2"))));
}

void TOntologyDataBaseWriter::TestRemove()
{
    QFETCH(QList<Ontology>, ontology);
    QFETCH(QStringList, ontologyNames);
    QFETCH(QString, ontologyName);

    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TestRemove.db";

    if(QFile::exists(dataBaseName))
    {
        if(!QFile::remove(dataBaseName))
        {
            QFAIL("can't remove testing database");
        }
    }

    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    for(int i = 0; i < ontology.size(); i++)
    {
        writer.writeOntology(ontologyNames.at(i), ontology.at(i));
    }

    QSet<QString> ontologyNamesCompare = writer.getOntologys();
    ontologyNamesCompare -= ontologyName;

    qWarning()<<"сэт с удалением :"<<ontologyNamesCompare;

    QSet<QString> compareSet = ontologyNamesCompare;
    writer.remove(ontologyName);

    const QSet<QString> realHash = writer.getOntologys();

    qWarning()<<"сэт полученный от функции :"<<realHash;

    QCOMPARE(compareSet, realHash);
}
