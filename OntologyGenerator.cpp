#include "OntologyGenerator.h"

OntologyGenerator::OntologyGenerator()
{
}

Ontology OntologyGenerator::generate(const int ClassCountSummary
                                         , const int classPropertiesCount
                                         , const int instancesCountSummary
                                         , const int classInstancesCount)
{
    QSet<QString> instancesSummary;
    QString className;
    QString instanceName;
    QString propertyName;
    bool canGenerate = true;
    //пока могу генерировать:
    while(canGenerate)
    {
        //если классы нельзы создавать
        //если суммарное количество классов > лимита
        if(allClasses().count() > classesSummary)
        {
            //прервать
            break;
        }
        //если есть классы для подклассов
        //если количество классов > 0
        if(allClasses().count() > 0)
        {
            className = generateClass();
            //создать случайный класс c надклассом в виде случайного класса
            addClass(className, allClasses().toList().at(qrand() % allClasses().count()));
        }
        //иначе
        else
        {
            //создать случайный класс без надкласса
            className = generateClass();
            addClass(className);
        }
        //пока классу можно добавлять свойства
        //пока кол-во свойств у классов <= общего предела свойств классов
        while(classProperties(className).count() <= classPropertiesCount)
        {
            //генерировать свойства для класса
            propertyName = generateProperty();
            //заполнить свойство класса значением
            addProperty(className, propertyName);
        }

        //пока инстансы можно создавать
        //пока количество инстансов <= общего предела инстансов
        while(allInstances() <= instancesCountSummary)
        {
            //если для класса можно добавить инстанс
            //если количество инстансов для класса <= предела инстансов для одного класса
            if(classInstances(className).count() <= ClassCountSummary)
            {
                //генерировать инстанс для класса
                instanceName = generateInstance();
                addInstance(className, instanceName);
                setPropertyValue();
            }
            //иначе
            else
            {
                //выход из цикла
                break;
            }
        }

    }
    return getOntology();
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
