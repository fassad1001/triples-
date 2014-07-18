#include "OntologyGenerator.h"

OntologyGenerator::OntologyGenerator()
{
}

QSet<Triple> OntologyGenerator::generate(const int ClassCountSummary
                                         , const int classPropertiesCount
                                         , const int instancesCountSummary
                                         , const int classInstancesCount)
{
    QSet<QString> classesSummary;
    QSet<QString> instancesSummary;
    QString className;
    QString instanceName;
    QString propertyName;
    bool canGenerate = true;
    //пока могу генерировать:
    while(canGenerate)
    {
        //если суммарное количество классов > лимита
        if(classesSummary.count() > ClassCountSummary)
        {
            break;
        }
        //если количество классов > 0
        //сгенерировать и запомнить новый класс
        className = generateClass();
        //запомнить сгенерированый класс
        classesSummary.insert(className);
        if(classesSummary.count() > 0)
        {
            //создать случайный класс c надклассом в виде случайного класса
            addClass(className, classesSummary.toList().at(qrand() % (classesSummary.count()-1)));
        }
        else
        {
            //создать случайный класс без надкласса
            addClass(className);
        }
        //пока количество инстансов у класса <= максимума количества инстансов для одного класса
        while(classInstances(className).count() <= classInstancesCount)
        {
            //если суммарное количество инстансов <= лимита
            if(instancesSummary.count() <= instancesCountSummary)
            {
                //сгенерировать инстанс и запомнить его имя
                instanceName = generateInstance();
                //добавить инстанс в набор инстансов
                instancesSummary.insert(instanceName);
                //добавить инстанс для класса
                addInstance(className, instanceName);
            }
        }
        //пока кол-во свойств у классов <= предела
        while(classProperties(className).count() <= classPropertiesCount)
        {
            //генерировать свойства для класса
            propertyName = generateProperty();
            addProperty(className, propertyName);
            setPropertyValue();
        }
    }
}

QString OntologyGenerator::generateClass() const
{
    return QString("classN") + QString::number(qrand());
}

QString OntologyGenerator::generateInstance() const
{
    return QString("instanceN") + QString::number(qrand());
}

QString OntologyGenerator::generateProperty() const
{
    return QString("propeertyN") + QString::number(qrand());
}

QString OntologyGenerator::generatePtopertyValue() const
{
    return QString("propeertyValueN") + QString::number(qrand());
}
