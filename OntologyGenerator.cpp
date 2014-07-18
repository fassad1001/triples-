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
        if(classesSummary.count() > 0)
        {
            //создать случайный класс c надклассом в виде случайного класса
        }
        else
        {
            //создать случайный класс без надкласса
        }
        //пока количество инстансов у класса <= максимума количества инстансов для одного класса
        while(classInstances(className) <= classInstancesCount)
        {
            //если суммарное количество инстансов <= лимита
            if(instancesSummary <= instancesCountSummary)
            {
                //генерировать инстанс для класса
            }
        }
        //пока кол-во свойств у классов <= предела
        while(classProperties(className) <= classPropertiesCount)
        {
            //генерировать свойства для класса
        }
    }
}

QString OntologyGenerator::generateClass() const
{

}
