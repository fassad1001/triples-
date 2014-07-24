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
    QFETCH(QString, dataBaseName);
    //пишу онтологию с именем
    OntologyDataBaseWriter writer = OntologyDataBaseWriter(dataBaseName);
    writer.writeOntology(ontologyName, ontology);
    //читаю
    OntologyDataBaseReader reader = OntologyDataBaseReader(dataBaseName);
    //если прочитал из БД то же что и записал то все правильно
    QCOMPARE(reader.readOntology(ontologyName),ontology);
}
