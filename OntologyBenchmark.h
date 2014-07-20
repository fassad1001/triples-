#ifndef ONTOLOGYBENCHMARK_H
#define ONTOLOGYBENCHMARK_H
#include "OntologyGenerator.h"
#include "BenchmarkResult.h"

class OntologyBenchmark : public BenchmarkResult
{
public:
    OntologyBenchmark();
    void timeStart();
    int getTime();

    int getMaxTime() const;
    int getMinTime() const;
    int getAverageTime() const;

    QString anyClass(const Ontology &ontology);
    QString anyInstance(const Ontology &ontology);
    QString anyProperty(const Ontology &ontology);
    QString anyValue(const Ontology &ontology);
    void randomize();


    QString OntologyDataToString(const int classCountSummary
                                 , const int classPropertiesCount
                                 , const int instancesCountSummary
                                 , const int classInstancesCount);
    QString getDataName() const;
    QString getFunctionName() const;
    void setFunctionName(const QString &functionName);

    int benchmarkIsMinimal(const Ontology &ontology);
    int benchmarkIsValid(const Ontology &ontology);
    int benchmarkMainSuperClass(const Ontology &ontology);
    int benchmarkSuperClasses(const Ontology &ontology);
    int benchmarkSubClasses(const Ontology &ontology);
    int benchmarkInstancesForNonProperties(const int &numberOfValues, const Ontology &ontology);
    int benchmarkInstancesForProperties(const int &numberOfValues, const Ontology &ontology);
    int benchmarkClassesForInstance(const Ontology &ontology);
    int benchmarkAllInstances(const Ontology &ontology);
    int benchmarkAllClasses(const Ontology &ontology);
    int benchmarkAllClassInstances(const int &numberOfClasses, const Ontology &ontology);
    int benchmarkInstanceProperties(const Ontology &ontology);
    int benchmarkPropertyValues(const Ontology &ontology);
    int benchmarkAnyClassInstances(const int &numberOfClasses, const Ontology &ontology);
    int benchmarkClassProperties(const Ontology &ontology);
    int benchmarkClassInstances(const Ontology &ontology);
    void setDataName(const QString &dataName);
private:
    QTime time_; //хранит время которое было затрачено на ту или иную функцию с данными
    QSet<int> timeCollection_; //хранит коллеуцию времени для выведения статистики
    bool start_;//говорит о том что метод start для счётчика был выполнен
    QString dataName_; //хранит в себе имя последних испльзованных данных
    QString functionName_; //хранит в себе имя последней тестируемой функции

};

#endif // ONTOLOGYBENCHMARK_H
