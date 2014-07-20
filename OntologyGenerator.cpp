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
    QSet<QString> classPropertiesItems;
    QSet<QString> classInstancesItems;
    bool canGenerate = true;
    //пока могу генерировать:
    while(canGenerate)
    {
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
        while(classProperties(className).count() < classPropertiesCount)
        {
            //генерировать свойства для класса
            propertyName = generateProperty();
            //заполнить свойство класса значением
            addProperty(className, propertyName);
        }

        //пока инстансы можно создавать
        //пока количество инстансов < общего предела инстансов
        if(allInstances().count() > instancesCountSummary)
        {
        }
        else
        {
        }
        while(allInstances().count() < instancesCountSummary)
        {
            //если для класса можно добавить инстанс
            //если количество инстансов класса < предела инстансов для одного класса
            if(classInstances(className).count() < classInstancesCount)
            {
                //генерировать инстанс для класса
                instanceName = generateInstance();
                addInstance(className, instanceName);
            }
            //иначе
            else
            {
                //выход из цикла
                break;

            }
        }
        //если классы нельзы создавать
        //если суммарное количество классов > лимита
        classInstancesItems = classInstances(className);
        classPropertiesItems = classProperties(className);
        foreach(QString classInstancesItem, classInstancesItems)
        {
            foreach(QString classPropertiesItem, classPropertiesItems)
            {
                QString propertyValue = generatePropertyValue();
                setPropertyValue(classInstancesItem, classPropertiesItem, propertyValue);
            }
        }

        if(allClasses().count() >= ClassCountSummary)
        {
            //прервать
            canGenerate = false;
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

QString OntologyGenerator::generatePropertyValue() const
{
    return QString("propeertyValueN") + QString::number(qrand());
}
