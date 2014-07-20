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



    QString getDataName() const;
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
private:
    QTime time_;
    QSet<int> timeCollection_; //хранит коллеуцию времени для выведения статистики
    bool start_;//говорит о том что метод start для счётчика был выполнен
    QTime time;

};

#endif // ONTOLOGYBENCHMARK_H
