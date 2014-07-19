#ifndef ONTOLOGYBENCHMARK_H
#define ONTOLOGYBENCHMARK_H
#include "OntologyGenerator.h"
#include "BenchmarkResult.h"

class OntologyBenchmark : public BenchmarkResult
{
public:
    enum FUNC
    {
        FUNC_classInstances,
        FUNC_classProperties,
        FUNC_anyClassInstances,
        FUNC_propertyValues,
        FUNC_instanceProperties,
        FUNC_allClassInstances,
        FUNC_allClasses,
        FUNC_allInstances,
        FUNC_classesForInstance,
        FUNC_instancesForProperties,
        FUNC_instancesForNonProperties,
        FUNC_subClasses,
        FUNC_superClasses,
        FUNC_mainSuperClass
    }

    OntologyBenchmark();
    void timeStart();
    int getTime();

    int getMaxTime() const;
    int getMinTime() const;
    int getAverageTime() const;

    void benchmarkOntology(const FUNC &nameOfFunction, const Ontology ontology);

    QString anyClass(const Ontology &ontology);
    QString anyInstance(const Ontology &ontology);
    QString anyProperty(const Ontology &ontology);
    QString anyValue(const Ontology &ontology);



    QString getDataName() const;
private:
    QTime time_;
    QSet<int> timeCollection_;
    bool start_;//говорит о том что метод start для счётчика был выполнен
    QTime time = QTime::currentTime();

};

#endif // ONTOLOGYBENCHMARK_H
