#include "OntologyBenchmark.h"

OntologyBenchmark::OntologyBenchmark()
{
}

void OntologyBenchmark::timeStart()
{
    if(start_)
    {
        time_.start();
        start_ = true;
    }
    else
    {
        time_.restart();
    }
}

int OntologyBenchmark::getMinTime() const
{
    QList<int> sortedTimeCollection = timeCollection_.toList();
    qSort(sortedTimeCollection.begin(), sortedTimeCollection.end());
    qWarning()<<sortedTimeCollection;if(sortedTimeCollection.isEmpty())
    {
        return int();
    }
    else
    {
        return sortedTimeCollection.first();
    }
}

int OntologyBenchmark::getMaxTime() const
{
    QList<int> sortedTimeCollection = timeCollection_.toList();
    qSort(sortedTimeCollection.begin(), sortedTimeCollection.end());
    qWarning()<<sortedTimeCollection;
    if(sortedTimeCollection.isEmpty())
    {
        return int();
    }
    else
    {
        return sortedTimeCollection.last();
    }
}

int OntologyBenchmark::getAverageTime() const
{
    int resulTime;
    foreach(int time, timeCollection_)
    {
        resulTime += time / timeCollection_.count();
    }
}

void OntologyBenchmark::benchmarkOntology(const OntologyBenchmark::FUNC &nameOfFunction
                                          , const Ontology ontology)
{
    FUNC funcName;
    switch(funcName)
    {
    case FUNC::FUNC_allClasses :
        timeStart();
        ontology.allClasses();
        break;
    case FUNC_allClassInstances:
        QString className = anyClass();
        timeStart();
        ontology.classInstances(className);
        break;
    case FUNC_allInstances:
        QString className = anyClass();
        timeStart();
        ontology.classInstances(className);
        break;
    case FUNC_anyClassInstances:
        QSet<QString> classNames = anyClass();
        QSet<
        timeStart();
        ontology.anyClassInstances(className);
        break;
    case FUNC_classesForInstance:

        break;
    case FUNC_classInstances:

        break;
    case FUNC_classProperties:

        break;
    case FUNC_instanceProperties:

        break;
    case FUNC_instancesForNonProperties:

        break;
    case FUNC_instancesForProperties:

        break;
    case FUNC_mainSuperClass:

        break;
    case FUNC_propertyValues:

        break;
    case FUNC_subClasses:

        break;
    case FUNC_superClasses:

        break;
    }

}

QString OntologyBenchmark::anyClass(const Ontology &ontology)
{
    if(!ontology.getStorage().isEmpty())
    {
        qsrand((uint)time.msec());
        QSet<QString> classes = ontology.allClasses();
        return classes.toList().at(qrand() % classes.count());
    }
    else
    {
        return QString();
    }
}

QString OntologyBenchmark::anyInstance(const Ontology &ontology)
{
    if(!ontology.getStorage().isEmpty())
    {
        qsrand((uint)time.msec());
        QSet<QString> instances = ontology.allInstances();
        return instances.toList().at(qrand() % instances.count());
    }
    else
    {
        return QString();
    }
}


QString OntologyBenchmark::anyProperty(const Ontology &ontology)
{
    if(!ontology.getStorage().isEmpty())
    {
        qsrand((uint)time.msec());
        QString anyClassItem = anyClass(ontology);
        QSet<QString> properties = ontology.classProperties(anyClassItem);
        return properties.toList().at(qrand() % properties.count());
    }
    else
    {
        return QString();
    }
}

QString OntologyBenchmark::anyValue(const Ontology &ontology)
{
    if(!ontology.getStorage().isEmpty())
    {
        qsrand((uint)time.msec());
        QSet<QString> values = ontology.propertyValues(anyProperty(ontology));
        QString value = values.toList().at(qrand() % values.count());
        return value;
    }
    else
    {
        return QString();
    }
}





