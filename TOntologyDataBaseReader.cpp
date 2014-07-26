#include "TOntologyDataBaseReader.h"

TOntologyDataBaseReader::TOntologyDataBaseReader()
{
}

void TOntologyDataBaseReader::TestReadOntology_data()
{

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
