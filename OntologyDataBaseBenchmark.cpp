#include "OntologyDataBaseBenchmark.h"

OntologyDataBaseBenchmark::OntologyDataBaseBenchmark()
{
}

int OntologyDataBaseBenchmark::exportToCSVBenchmark(const int &size)
{
    setFunctionName("exportToCSVBenchmark");
    setDataName(QString::number(size));
    //генерирую имя онтологии
    const QString dataBaseName = getFunctionName() + getDataName() + ".db";
    const QString ontologyName = "ontology" + QString::number(size);
    const QString fileName = "exportToCSVBenchmark" + QString::number(size) + ".csv";
    //генерирую онтологию
    const Ontology ontology = generate(size);
    //пишу ее в БД
    OntologyDataBaseWriter(dataBaseName).writeOntology(ontologyName, ontology);
    //начинаю таймер
    timeStart();
    //пишу в CSV
    OntologyDataBaseReader(dataBaseName).exportToCSV(fileName, ontologyName);
    //останавливаю таймер
    //возвращаю результат
    return getTime();
}

int OntologyDataBaseBenchmark::importFromCSVBenchmark(const int &size)
{
    setFunctionName("importFromCSVBenchmark");
    setDataName(QString::number(size));
    //генерирую имя онтологии
    const QString dataBaseName = getFunctionName() + getDataName() + ".db";
    const QString ontologyName = "ontology" + QString::number(size);
    const QString fileName = "exportToCSVBenchmark" + QString::number(size) + ".csv";
    //генерирую онтологию
    const Ontology ontology = generate(size);
    //пишу ее в БД
    OntologyDataBaseWriter(dataBaseName).writeOntology(ontologyName, ontology);
    //пишу в CSV
    OntologyDataBaseReader(dataBaseName).exportToCSV(fileName, ontologyName);
    //начинаю таймер
    timeStart();
    OntologyDataBaseWriter(dataBaseName).importFromCSV(fileName, ontologyName);
    //останавливаю таймер
    //возвращаю результат
    return getTime();
}

Ontology OntologyDataBaseBenchmark::generate(const int &size)
{
    return OntologyGenerator().generate(size, 40, 30, 4);
}
