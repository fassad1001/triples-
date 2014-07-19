#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

#include "TPair.h"

#include "TTripleStorage.h"

#include "BenchmarkResult.h"

#include "TOntology.h"

#include "TOntologyBuilder.h"

#include "OntologyGenerator.h"

#include "OntologyBenchmark.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //    TTriples Ttriples;
    //    QTest::qExec(&Ttriples);

    //    TPair pair;
    //    QTest::qExec(&pair);

//    TTripleStorage TtripleStorage;
//    QTest::qExec(&TtripleStorage);

//    TOntology ontology;
//    QTest::qExec(&ontology);

//    TOntologyBuilder ontologyBuilder;
//    QTest::qExec(&ontologyBuilder);

    OntologyGenerator gener;
    OntologyBenchmark benchmark;
    Ontology test;
    test = gener.generate(100, 1, 211, 1);
    qWarning()<<"выдаю любой инстанс "<<benchmark.anyInstance(test);
    qWarning()<<"выдаю любой класс "<<benchmark.anyClass(test);
    qWarning()<<"выдаю любое свойство "<<benchmark.anyProperty(test);
    qWarning()<<"выдаю любое значение свойства "<<benchmark.anyValue(test);
    qWarning()<<"thats all!"<<test.allClasses().count();




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
