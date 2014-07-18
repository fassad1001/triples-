#include "OntologyBuilder.h"

OntologyBuilder::OntologyBuilder()
{
}

OntologyBuilder::OntologyBuilder(const QSet<Triple> &triples) :
    Ontology(triples)
{
}

void OntologyBuilder::addClass(const QString &className, const QString &parentClassName)
{
    const QSet<QString> allClassItems = allClasses();
    //если все классы содержат вводный класс
    if(allClassItems.contains(className))
    {
        //return;
        return;
    }
    if(parentClassName != QString())
    {
        if(!allClassItems.contains(parentClassName))
        {
            return;
        }
    }
    //добавить (имя_класса, IS, CLASS)
    add(className, Ontology::IS, Ontology::CLASS);
    //если parentClassName != QString()
    if(parentClassName != QString())
    {
        if(allClassItems.contains(parentClassName))
        {
            //добавить (имя_родительского_класса,CONTAINS,имя_класса)
            add(parentClassName, Ontology::CONTAINS, className);
        }
    }
}

void OntologyBuilder::addProperty(const QString &className, const QString &propertyName)
{
    //если все классы содержат класс имя_класса
    if(!allClasses().contains(className))
    {
        return;
    }
    //добавить (имя_класса, HAS_PROPERTY, имя_свойства)
    add(className, Ontology::HAS_PROPERTY, propertyName);
}

void OntologyBuilder::addInstance(const QString &className, const QString &instanceName)
{
    //если все инстансы содержат имя инстанса
    if(allInstances().contains(instanceName) || !allClasses().contains(className))
    {
        //return;
        return;
    }
    //добавить (имя_инстанса, IS, имя_класса)
    add(instanceName, Ontology::IS, className);
}

void OntologyBuilder::setPropertyValue(const QString &instanceName, const QString &propertyName, const QString value)
{
    //если свойства инстанса имя_инстанса (instanceProperties) содержат свойство имя_свойства
    if(!instanceProperties(instanceName).contains(propertyName))
    {
        //return;
        return;
    }
    else
    {
        //на случай замены значения
        updateObject(instanceName, propertyName, value);
    }
    //добавить (имя_инстанса, имя_свойства, значение_свойства)
    add(instanceName, propertyName, value);
}

Ontology OntologyBuilder::getOntology() const
{
    return(Ontology(getStorage()));
}
