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
        //если классы нельзы создавать
        //если суммарное количество классов > лимита
        if(allClasses().count() >= ClassCountSummary)
        {
            qWarning()<<"классов достаточно";
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
            qWarning()<<">>создаю класс с подклассом";
        }
        //иначе
        else
        {
            //создать случайный класс без надкласса
            className = generateClass();
            addClass(className);
            qWarning()<<">>создаю класс без подкласса";
        }
        //пока классу можно добавлять свойства
        //пока кол-во свойств у классов <= общего предела свойств классов
        while(classProperties(className).count() < classPropertiesCount)
        {
            //генерировать свойства для класса
            propertyName = generateProperty();
            //заполнить свойство класса значением
            addProperty(className, propertyName);
            qWarning()<<"создаю свойство";
        }

        //пока инстансы можно создавать
        //пока количество инстансов < общего предела инстансов
        qWarning()<<"проверяю, "<<allInstances().count()<<"<"<<instancesCountSummary;
        if(allInstances().count() > instancesCountSummary)
        {
            qWarning()<<"я не могу создавать инстансы";
        }
        else
        {
            qWarning()<<"начинаю создавать инстансы для класса "<<className;
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
                qWarning()<<"создаю инстанс"<<instanceName<<" для "<<className;
            }
            //иначе
            else
            {
                //выход из цикла
                qWarning()<<"прекращаю создавать инстансы";
                break;

            }
        }
        qWarning()<<"у класса "<<className<<" есть инстансы "<<classInstances(className);

    }
    classInstancesItems = classInstances(className);
    classPropertiesItems = classProperties(className);
    foreach(QString classInstancesItem, classInstancesItems)
    {
        foreach(QString classPropertiesItem, classPropertiesItems)
        {
            setPropertyValue(classInstancesItem, classPropertiesItem, generatePropertyValue());
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
