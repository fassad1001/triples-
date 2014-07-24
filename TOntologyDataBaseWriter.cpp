#include "TOntologyDataBaseWriter.h"

TOntologyDataBaseWriter::TOntologyDataBaseWriter()
{
}

void TOntologyDataBaseWriter::TestWriteOntology_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <QString> ("dataBaseName");
    QTest::addColumn <Ontology> ("ontology");

    QTest::newRow("new DB1_1")
            << "ontology1"
            << "testDB1write.db"
            << (Ontology(QSet<Triple>()
                         <<Triple("1", "1", "1")
                         <<Triple("2", "2", "2")
                         <<Triple("3", "3", "3")));

    QTest::newRow("new DB1_2")
            << "ontology1"
            << "testDB1write.db"
            << (Ontology(QSet<Triple>()
                         <<Triple("4", "4", "4")
                         <<Triple("4", "4", "4")
                         <<Triple("4", "4", "4")));
}

void TOntologyDataBaseWriter::TestWriteOntology()
{
    //входные данные это онтология, имя онтологии, имя файла БД
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    QFETCH(QString, dataBaseName);
    //пишу онтологию с именем
    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    //читаю
    OntologyDataBaseReader reader = OntologyDataBaseReader(dataBaseName);
    //если прочитал из БД то же что и записал то все правильно
    QCOMPARE(reader.readOntology(ontologyName),ontology);
}

void TOntologyDataBaseWriter::TestRemove_data()
{
    QTest::addColumn <QString> ("ontologyName");
    QTest::addColumn <QString> ("dataBaseName");
    QTest::addColumn <Ontology> ("ontology");

    QTest::newRow("new DB1_1")
            << "ontology1"
            << "testDB1write.db"
            << (Ontology(QSet<Triple>()
                         <<Triple("1", "1", "1")
                         <<Triple("2", "2", "2")
                         <<Triple("3", "3", "3")));

    QTest::newRow("new DB1_2")
            << "ontology2"
            << "testDB1write.db"
            << (Ontology(QSet<Triple>()
                         <<Triple("4", "4", "4")
                         <<Triple("5", "5", "5")
                         <<Triple("6", "6", "6")));
}

void TOntologyDataBaseWriter::TestRemove()
{
    //исхдные данные это онтология
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    QFETCH(QString, dataBaseName);

    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    writer.remove(ontologyName);
    QCOMPARE(writer.isExists(ontologyName), false);
    //записать онтологию в БД
    //проверить на существование методом exists
    //если существует то неОК
    //если не существует то ОК
}
