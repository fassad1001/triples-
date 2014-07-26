#include "TOntologyDataBaseReader.h"

TOntologyDataBaseReader::TOntologyDataBaseReader()
{
}

void TOntologyDataBaseReader::TestReadOntology_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("ontologyName");

    //проверить удаление конкретной онтологии из множества, проверить удаление несуществующей онтологии
    QTest::newRow("full-ontology")
    << (Ontology(QSet<Triple>()
                 <<Triple("class1", Ontology::IS, Ontology::CLASS)
                 <<Triple("class2", Ontology::IS, Ontology::CLASS)
                 <<Triple("class3", Ontology::IS, Ontology::CLASS)
                 <<Triple("class1", Ontology::CONTAINS, "class2")
                 <<Triple("class2", Ontology::CONTAINS, "class3")
                 <<Triple("instance1", Ontology::IS, "class2")))
       <<"ontology1";

    QTest::newRow("empty-ontology")
    << (Ontology(QSet<Triple>()))
        <<"ontology1";
}

void TOntologyDataBaseReader::TestReadOntology()
{
    //входные данные это онтология, имя онтологии, имя файла БД
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TestReadOntology.db";
    //пишу онтологию с именем
    if(QFile::exists(dataBaseName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(dataBaseName))
        {
            //тест падает
            QFAIL("не могу удалить файл БД");
        }
    }
    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    //читаю
    OntologyDataBaseReader reader = OntologyDataBaseReader(dataBaseName);
    //если прочитал из БД то же что и записал то все правильно
    QCOMPARE(reader.readOntology(ontologyName),ontology);
}
