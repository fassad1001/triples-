#include <QCoreApplication>

#include "TTriples.h"

#include "TPair.h"

#include "TTripleStorage.h"

#include "BenchmarkResult.h"

#include "TOntology.h"

#include "TOntologyBuilder.h"

#include "OntologyGenerator.h"

#include "OntologyBenchmark.h"

#include "TOntologyDataBaseInterface.h"

#include "TOntologyDataBaseWriter.h"

#include "TOntologyDataBaseReader.h"

#include "OntologyDataBaseBenchmark.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    TPair pair;
    QTest::qExec(&pair);

    TTripleStorage TtripleStorage;
    QTest::qExec(&TtripleStorage);

    TOntology ontology;
    QTest::qExec(&ontology);

    TOntologyBuilder ontologyBuilder;
    QTest::qExec(&ontologyBuilder);

    TOntologyDataBaseWriter writer;
    QTest::qExec(&writer);

    TOntologyDataBaseReader reader;
    QTest::qExec(&reader);


    //    QFile::remove("test.db");
    //    OntologyDataBaseWriter wr = OntologyDataBaseWriter("test.db");

    //    wr.writeOntology("ontologyName2", Ontology(QSet<Triple>()
    //                                               <<Triple("1", "1", "1")
    //                                               <<Triple("2", "2", "2")
    //                                               <<Triple("3", "3", "3")
    //                                               <<Triple("5", "5", "5")
    //                                               <<Triple("6", "6", "6")
    //                                               <<Triple("7", "7", "7")));


    //    wr.writeOntology("ontologyName3", Ontology(QSet<Triple>()
    //                                               <<Triple("1", "1", "1")
    //                                               <<Triple("2", "2", "2")
    //                                               <<Triple("3", "3", "3")
    //                                               <<Triple("5", "5", "5")
    //                                               <<Triple("6", "6", "6")
    //                                               <<Triple("7", "7", "7")));
        OntologyDataBaseBenchmark benchmark;
        qWarning()<<"start benchmark";
        for(int i = 100; i<= 1000; i += 100)
        {
            const Ontology ontology = benchmark.generate(i);
            qWarning()<<"i="<<QString::number(i);
            qWarning()<<"exportToCSVBenchmark"<<benchmark.exportToCSVBenchmark(ontology);
            benchmark.commit();
            qWarning()<<"importFromCSVBenchmark"<<benchmark.importFromCSVBenchmark(ontology);
            benchmark.commit();
        }
        const QString fileName = "D:/отчёты/benchmark.csv";
        QFile::remove(fileName);
        benchmark.writeFile(fileName);

    //    OntologyGenerator generator;
    //    OntologyBenchmark benchmark;
    //    Ontology ontology;
    //    int classes;
    //    int classProperties;
    //    int instances;
    //    int classInstances;
    //    int time;
    //    for(int funcNum = 0; funcNum <= 15; funcNum += 1)
    //    {
    //        for(int classes = 10; classes <= 10; classes += 10)
    //        {
    //            for(int classProperties = 10; classProperties <= 100; classProperties += 10)
    //            {
    //                for(int instances = 10; instances <= 10; instances += 10)
    //                {
    //                    for(int classInstances = 10; classInstances <= 10; classInstances += 10)
    //                    {
    //                        ontology = generator.generate(classes, classProperties, instances, classInstances);
    //                        //выполняю бенчмарк метод
    //                        qWarning()<<benchmark.OntologyDataToString(classes, classProperties, instances, classInstances);
    //                        switch(funcNum)
    //                        {
    //                        case 0:
    //                            qWarning()<<"benchmarkIsMinimal";
    //                            time = benchmark.benchmarkIsMinimal(ontology);
    //                            break;
    //                        case 1:
    //                            qWarning()<<"benchmarkIsValid";
    //                            time = benchmark.benchmarkIsValid(ontology);
    //                            break;
    //                        case 2:
    //                            qWarning()<<"benchmarkMainSuperClass";
    //                            time = benchmark.benchmarkMainSuperClass(ontology);
    //                            break;
    //                        case 3:
    //                            qWarning()<<"benchmarkSuperClasses";
    //                            time = benchmark.benchmarkSuperClasses(ontology);
    //                            break;
    //                        case 4:
    //                            qWarning()<<"benchmarkSubClasses";
    //                            time = benchmark.benchmarkSubClasses(ontology);
    //                            break;
    //                        case 5:
    //                            qWarning()<<"benchmarkInstancesForNonProperties";
    //                            time = benchmark.benchmarkInstancesForNonProperties(5, ontology);
    //                            break;
    //                        case 6:
    //                            qWarning()<<"benchmarkInstancesForProperties";
    //                            time = benchmark.benchmarkInstancesForProperties(5, ontology);
    //                            break;
    //                        case 7:
    //                            qWarning()<<"benchmarkClassesForInstance";
    //                            time = benchmark.benchmarkClassesForInstance(ontology);
    //                            break;
    //                        case 8:
    //                            qWarning()<<"benchmarkAllInstances";
    //                            time = benchmark.benchmarkAllInstances(ontology);
    //                            break;
    //                        case 9:
    //                            qWarning()<<"benchmarkAllClasses";
    //                            time = benchmark.benchmarkAllClasses(ontology);
    //                            break;
    //                        case 10:
    //                            qWarning()<<"benchmarkAllClassInstances";
    //                            time = benchmark.benchmarkAllClassInstances(5, ontology);
    //                            break;
    //                        case 11:
    //                            qWarning()<<"benchmarkInstanceProperties";
    //                            time = benchmark.benchmarkInstanceProperties(ontology);
    //                            break;
    //                        case 12:
    //                            qWarning()<<"benchmarkPropertyValues";
    //                            time = benchmark.benchmarkPropertyValues(ontology);
    //                            break;
    //                        case 13:
    //                            qWarning()<<"benchmarkAnyClassInstances";
    //                            time = benchmark.benchmarkAnyClassInstances(5, ontology);
    //                            break;
    //                        case 14:
    //                            qWarning()<<"benchmarkClassProperties";
    //                            time = benchmark.benchmarkClassProperties(ontology);
    //                            break;
    //                        case 15:
    //                            qWarning()<<"setDataName";
    //                            time = benchmark.benchmarkClassInstances(ontology);
    //                            break;
    //                        }
    //                        benchmark.setTime(benchmark.getFunctionName()
    //                                          ,benchmark.OntologyDataToString(classes, classProperties, instances, classInstances)
    //                                          ,time);
    //                    }
    //                }
    //            }
    //        }
    //    }
    //    benchmark.writeFile("D:/отчёты/benchmark4.csv");


    //    qsrand(42);

    //    int dataSize;
    //    int sparseness = 1000;

    //    int funcChoose;

    //    BenchmarkResult bench;

    //    for(funcChoose = 1; funcChoose <= 6; funcChoose++)
    //    {
    //        for (sparseness = 100; sparseness <= 10000; sparseness*=10)
    //        {
    //            for (dataSize = 1000; dataSize <=1000000; dataSize*=10)
    //            {
    //                const QSet<Triple> triples = Triple::randoms(dataSize, sparseness);
    //                const int inputSize = 100;

    //                QString funcName;

    //                int averageTime = 0;
    //                for(int i = 0; i < inputSize; i++)
    //                {
    //                    const QString randNumber = QString::number(qrand() % dataSize);
    //                    const TripleStorage storage(triples);

    //                    QSet<Pair> pairs;
    //                    QSet<QString> strings;

    //                    QTime time;
    //                    time.start();

    //                    switch (funcChoose)
    //                    {
    //                    case 1:

    //                        funcName = "subjectsAndObjects";
    //                        pairs = storage.subjectsAndObjects(randNumber);
    //                        break;
    //                    case 2:

    //                        funcName = "predicatesAndObjects";
    //                        pairs = storage.predicatesAndObjects(randNumber);
    //                        break;
    //                    case 3:

    //                        funcName = "subjectAndPredicatesFor";
    //                        pairs = storage.subjectAndPredicatesFor(randNumber);
    //                        break;
    //                    case 4:

    //                        funcName = "objectsFor";
    //                        strings = storage.objectsFor(randNumber, QString::number(qrand() % dataSize));
    //                        break;
    //                    case 5:

    //                        funcName = "subjectsFor";
    //                        strings = storage.subjectsFor(randNumber, QString::number(qrand() % dataSize));
    //                        break;
    //                    case 6:

    //                        funcName = "predicatesFor";
    //                        strings = storage.predicatesFor(randNumber, QString::number(qrand() % dataSize));
    //                        break;
    //                    }

    //                    averageTime += time.elapsed();
    //                    pairs.clear();
    //                }
    //                averageTime /= inputSize;

    //                const QString dataName = "ds: " + QString::number(dataSize)
    //                        + " s: " + QString::number(sparseness)
    //                        + " is: " + QString::number(inputSize);

    //                bench.setTime(funcName, dataName, averageTime);
    //            }
    //        }

    //    }


    //    qWarning() << bench.toString();

    //    bench.writeFile("D:/отчёты/benchmark.csv");

    //    return 0;
}
