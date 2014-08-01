#include "OntologyDataBaseBenchmark.h"

OntologyDataBaseBenchmark::OntologyDataBaseBenchmark()
{
}

int OntologyDataBaseBenchmark::exportToCSVBenchmark(const Ontology &ontology)
{
    setFunctionName("exportToCSVBenchmark");
    const int size = ontology.allClasses().count();
    setDataName(QString::number(size));
    //генерирую имя онтологии
    const QString dataBaseName = getFunctionName() + getDataName() + ".db";
    const QString ontologyName = "ontology" + QString::number(size);
    const QString fileName = "exportToCSVBenchmark" + QString::number(size) + ".csv";
    if(QFile::exists(dataBaseName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(dataBaseName))
        {
            qWarning()<<"не могу удалить файл БД";
        }
    }
    //пишу ее в БД
    OntologyDataBaseWriter(dataBaseName).writeOntology(ontologyName, ontology);
    //начинаю таймер
    timeStart();
    //пишу в CSV
    OntologyDataBaseReader(dataBaseName).exportToCSV(fileName, ontologyName);
    //останавливаю таймер
    //возвращаю результат
    const int time = getTime();
    setTimeLocal(time);
    return time;
}

int OntologyDataBaseBenchmark::importFromCSVBenchmark(const Ontology &ontology)
{
    setFunctionName("importFromCSVBenchmark");
    const int size = ontology.allClasses().count();
    setDataName(QString::number(size));
    //генерирую имя онтологии
    const QString dataBaseName = getFunctionName() + getDataName() + ".db";
    const QString ontologyName = "ontology" + QString::number(size);
    const QString fileName = "exportToCSVBenchmark" + QString::number(size) + ".csv";
    if(QFile::exists(dataBaseName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(dataBaseName))
        {
            qWarning()<<"не могу удалить файл БД";
        }
    }
    //пишу ее в БД
    OntologyDataBaseWriter(dataBaseName).writeOntology(ontologyName, ontology);
    //пишу в CSV
    OntologyDataBaseReader(dataBaseName).exportToCSV(fileName, ontologyName);
    //начинаю таймер
    timeStart();
    OntologyDataBaseWriter(dataBaseName).importFromCSV(fileName, ontologyName);
    //останавливаю таймер
    //возвращаю результат
    const int time = getTime();
    setTimeLocal(time);
    return time;
}

void OntologyDataBaseBenchmark::commit()
{
    setTime(getFunctionName(), getDataName(), getLocalTime());
}

Ontology OntologyDataBaseBenchmark::generate(const int &size)
{
    return OntologyGenerator().generate(size, 0, 1, 0);
}
