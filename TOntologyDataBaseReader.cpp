#include "TOntologyDataBaseReader.h"

TOntologyDataBaseReader::TOntologyDataBaseReader()
{
}

void TOntologyDataBaseReader::TestReadOntology_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("ontologyName");

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

void TOntologyDataBaseReader::TestImportCSV_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("ontologyName");

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

void TOntologyDataBaseReader::TestImportCSV()
{
    //задать стартовые параметры (имя онтологии и онтологию)
    QFETCH(Ontology, ontology);
    QFETCH(QString, ontologyName);
    //сгенерировать имя БД и имя файла
    const QString dataTag = QTest::currentDataTag();
    const QString dataBaseName = dataTag + "TestReadOntology.db";
    const QString fileName = dataTag + "TestReadOntology.csv";
    //удалить файлы если они есть (оба)
    if(QFile::exists(dataBaseName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(dataBaseName))
        {
            //тест падает
            QFAIL("не могу удалить файл БД");
        }
    }
    if(QFile::exists(fileName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(fileName))
        {
            //тест падает
            QFAIL("не могу удалить файл БД");
        }
    }
    //создать писателя и читателя
    OntologyDataBaseReader reader(dataBaseName);
    OntologyDataBaseWriter writer(fileName);
    //записать онтологию в БД
    writer.writeOntology(ontologyName, ontology);
    //записать онтологию в файл
    reader.exportToCSV(fileName, ontologyName);
    //прочитать онтологию из файла
    Ontology compareOntology = writer.importFromCSV(fileName, ontologyName);
    //сравнить прочитанное с тем что записывали
    QCOMPARE(ontology == compareOntology, true);
}
