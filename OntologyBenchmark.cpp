#include "OntologyBenchmark.h"

OntologyBenchmark::OntologyBenchmark() :
    start_(false)
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

int OntologyBenchmark::getLocalTime()
{
    return intTime_;
}

void OntologyBenchmark::resetStatistic()
{
    timeCollection_.clear();
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
    functionName_ = "classInstances";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkClassProperties(const Ontology &ontology)
{
    QString classItem = anyClass(ontology);
    timeStart();
    ontology.classProperties(classItem);
    functionName_ = "classProperties";
    dataName_ = QString();
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
    functionName_ = "anyClassInstances";
    dataName_ = "classes:" + QString::number(numberOfClasses);
    return getTime();
}



int OntologyBenchmark::benchmarkPropertyValues(const Ontology &ontology)
{
    QString propertyName = anyProperty(ontology);
    timeStart();
    ontology.propertyValues(propertyName);
    functionName_ = "propertyValues";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkInstanceProperties(const Ontology &ontology)
{
    QString instanceName = anyInstance(ontology);
    timeStart();
    ontology.instanceProperties(instanceName);
    functionName_ = "instanceProperties";
    dataName_ = QString();
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
    functionName_ = "allClassInstances";
    dataName_ = "classes:" + QString::number(numberOfClasses);
    return getTime();
}

int OntologyBenchmark::benchmarkAllClasses(const Ontology &ontology)
{
    timeStart();
    ontology.allClasses();
    functionName_ = "allClasses";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkAllInstances(const Ontology &ontology)
{
    timeStart();
    ontology.allInstances();
    functionName_ = "allInstances";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkClassesForInstance(const Ontology &ontology)
{
    QString instanceName = anyInstance(ontology);
    timeStart();
    ontology.instanceProperties(instanceName);
    functionName_ = "classesForInstance";
    dataName_ = QString();
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
    functionName_ = "instancesForProperties";
    dataName_ = "values:" + QString::number(numberOfValues);
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
    functionName_ = "instancesForNonProperties";
    dataName_ = "values:" + QString::number(numberOfValues);
    return getTime();
}

int OntologyBenchmark::benchmarkSubClasses(const Ontology &ontology)
{
    QString className = anyClass(ontology);
    timeStart();
    ontology.subClasses(className);
    functionName_ = "subClasses";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkSuperClasses(const Ontology &ontology)
{
    QString className = anyClass(ontology);
    timeStart();
    ontology.superClasses(className);
    functionName_ = "superClasses";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkMainSuperClass(const Ontology &ontology)
{
    QString instanceName1 = anyInstance(ontology);
    QString instanceName2 = anyInstance(ontology);
    timeStart();
    ontology.mainSuperClass(instanceName1, instanceName2);
    functionName_ = "mainSuperClass";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkIsValid(const Ontology &ontology)
{
    timeStart();
    ontology.isValid();
    functionName_ = "isValid";
    dataName_ = QString();
    return getTime();
}

int OntologyBenchmark::benchmarkIsMinimal(const Ontology &ontology)
{
    timeStart();
    ontology.isMinimal(QSet<Pair>()<<Pair("1","2"));
    functionName_ = "isMinimal";
    dataName_ = QString();
    return getTime();
}

QString OntologyBenchmark::anyClass(const Ontology &ontology)
{

    if(!ontology.allClasses().isEmpty())
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
    if(!ontology.allInstances().isEmpty())
    {
        QSet<QString> instances = ontology.allInstances();
        return instances.toList().at(rand() % instances.count());
    }
    else
    {
        return QString();
    }
}


QString OntologyBenchmark::anyProperty(const Ontology &ontology)
{

    if(!ontology.allClasses().isEmpty())
    {
        QString anyClassItem = anyClass(ontology);
        QSet<QString> properties = ontology.classProperties(anyClassItem);
        if(ontology.classProperties(anyClassItem).isEmpty())
        {
            return QString();
        }
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

    if(!ontology.getStorage().isEmpty())
    {
        const QString propertyName = anyProperty(ontology);
        const QSet<QString> values = ontology.propertyValues(propertyName);
        if(values.isEmpty())
        {
            return QString();
        }
        QString value = values.toList().at(rand() % values.count());
        return value;
    }
    else
    {
        return QString();
    }
}

QString OntologyBenchmark::OntologyDataToString(const int classCountSummary, const int classPropertiesCount, const int instancesCountSummary, const int classInstancesCount)
{
    return QString()
            +"Ont:cl(S)-"
            +QString::number(classCountSummary)
            +"&clProp-"
            +QString::number(classPropertiesCount)
            +"&inst(S)-"
            +QString::number(instancesCountSummary)
            +"&clInstance-"
            +QString::number(classInstancesCount)
            +"&allProp-"
            +QString::number(classCountSummary*classPropertiesCount);
}

QString OntologyBenchmark::getDataName() const
{
    return  dataName_;
}

QString OntologyBenchmark::getFunctionName() const
{
    return functionName_;
}

void OntologyBenchmark::setFunctionName(const QString &functionName)
{
    functionName_ = functionName;
}

void OntologyBenchmark::setTimeLocal(int time)
{
    intTime_ = time;
}

void OntologyBenchmark::setDataName(const QString &dataName)
{
    dataName_ = dataName;
}





