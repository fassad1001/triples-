#include "OntologyBenchmark.h"

OntologyBenchmark::OntologyBenchmark() :
    time(QTime::currentTime())
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

int OntologyBenchmark::getTime()
{
    return time_.restart();
}

int OntologyBenchmark::getMinTime() const
{
    QList<int> sortedTimeCollection = timeCollection_.toList();
    qSort(sortedTimeCollection.begin(), sortedTimeCollection.end());
    if(sortedTimeCollection.isEmpty())
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
    return resulTime;
}

int OntologyBenchmark::benchmarkClassInstances(const Ontology &ontology)
{
    QString classItem = anyClass(ontology);
    timeStart();
    ontology.classInstances(classItem);
    return getTime();
}

int OntologyBenchmark::benchmarkClassProperties(const Ontology &ontology)
{
    QString classItem = anyClass(ontology);
    timeStart();
    ontology.classProperties(classItem);
    return getTime();
}

int OntologyBenchmark::benchmarkAnyClassInstances(const int &numberOfClasses, const Ontology &ontology)
{
    QStringList classes;
    for(int i = 1; i <= numberOfClasses; i++)
    {
        classes += anyClass(ontology);
    }
    timeStart();
    ontology.anyClassInstances(classes);
    return getTime();
}



int OntologyBenchmark::benchmarkPropertyValues(const Ontology &ontology)
{
    QString propertyName = anyProperty(ontology);
    timeStart();
    ontology.propertyValues(propertyName);
    return getTime();
}

int OntologyBenchmark::benchmarkInstanceProperties(const Ontology &ontology)
{
    QString instanceName = anyInstance(ontology);
    timeStart();
    ontology.instanceProperties(instanceName);
    return getTime();
}


int OntologyBenchmark::benchmarkAllClassInstances(const int &numberOfClasses, const Ontology &ontology)
{
    QStringList classes;
    for(int i = 1; i <= numberOfClasses; i++)
    {
        classes += anyClass(ontology);
    }
    timeStart();
    ontology.allClassInstances(classes);
    return getTime();
}

int OntologyBenchmark::benchmarkAllClasses(const Ontology &ontology)
{
    timeStart();
    ontology.allClasses();
    return getTime();
}

int OntologyBenchmark::benchmarkAllInstances(const Ontology &ontology)
{
    timeStart();
    ontology.allInstances();
    return getTime();
}

int OntologyBenchmark::benchmarkClassesForInstance(const Ontology &ontology)
{
    QString instanceName = anyInstance(ontology);
    timeStart();
    ontology.instanceProperties(instanceName);
    return getTime();
}

int OntologyBenchmark::benchmarkInstancesForProperties(const int &numberOfValues, const Ontology &ontology)
{
    MyHash values;
    for(int i = 1; i <= numberOfValues; i++)
    {
        values.insert(anyProperty(ontology), anyValue(ontology));
    }
    timeStart();
    ontology.instancesForProperties(values);
    return getTime();
}

int OntologyBenchmark::benchmarkInstancesForNonProperties(const int &numberOfValues, const Ontology &ontology)
{
    MyHash values;
    for(int i = 1; i <= numberOfValues; i++)
    {
        values.insert(anyProperty(ontology), anyValue(ontology));
    }
    timeStart();
    ontology.instancesForNonProperties(values);
    return getTime();
}

int OntologyBenchmark::benchmarkSubClasses(const Ontology &ontology)
{
    QString className = anyClass(ontology);
    timeStart();
    ontology.subClasses(className);
    return getTime();
}

int OntologyBenchmark::benchmarkSuperClasses(const Ontology &ontology)
{
    QString className = anyClass(ontology);
    timeStart();
    ontology.superClasses(className);
    return getTime();
}

int OntologyBenchmark::benchmarkMainSuperClass(const Ontology &ontology)
{
    QString instanceName1 = anyInstance(ontology);
    QString instanceName2 = anyInstance(ontology);
    timeStart();
    ontology.mainSuperClass(instanceName1, instanceName2);
    return getTime();
}

int OntologyBenchmark::benchmarkIsValid(const Ontology &ontology)
{
    timeStart();
    ontology.isValid();
    return getTime();
}

int OntologyBenchmark::benchmarkIsMinimal(const Ontology &ontology)
{
    timeStart();
    ontology.isMinimal(QSet<Pair>()<<Pair("1","2"));
    return getTime();
}

QString OntologyBenchmark::anyClass(const Ontology &ontology)
{
    randomize();
    if(!ontology.getStorage().isEmpty())
    {
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
    randomize();
    if(!ontology.getStorage().isEmpty())
    {
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
    randomize();
    if(!ontology.getStorage().isEmpty())
    {
        QString anyClassItem = anyClass(ontology);
        QSet<QString> properties = ontology.classProperties(anyClassItem);
        int randomNumber = qrand();
        return properties.toList().at(randomNumber % properties.count());
    }
    else
    {
        return QString();
    }
}

QString OntologyBenchmark::anyValue(const Ontology &ontology)
{
    randomize();
    if(!ontology.getStorage().isEmpty())
    {
        const QString propertyName = anyProperty(ontology);
        const QSet<QString> values = ontology.propertyValues(propertyName);
        QString value = values.toList().at(rand() % values.count());
        return value;
    }
    else
    {
        return QString();
    }
}

void OntologyBenchmark::randomize()
{
    time = QTime::currentTime();
}





