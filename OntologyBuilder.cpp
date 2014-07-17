#include "OntologyBuilder.h"

OntologyBuilder::OntologyBuilder()
{
}

void OntologyBuilder::addClass(const QString &className, const QString &parentClassName)
{
    QSet<QString> allClassItems = allClasses();
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
    if(allClasses().contains(className))
    {
        //для каждого класса
        foreach(QString classItem, allClasses())
        {
            //если класс содержит свойство имя_свойства
            if(classProperties(classItem).contains(propertyName))
            {
                //return;
                return;
            }
        }
    }
    else
    {
        return;
    }
    //добавить (имя_класса, HAS_PROPERTY, имя_свойства)
    add(className, Ontology::HAS_PROPERTY, propertyName);
}

Ontology OntologyBuilder::getOntology() const
{
    return(Ontology(getStorage()));
}
