#include "OntologyBuilder.h"

OntologyBuilder::OntologyBuilder()
{
}

void OntologyBuilder::addClass(const QString &className, const QString &parentClassName)
{
    //если все классы содержат вводный класс
    if(allClasses().contains(className))
    {
        //return;
        return;
    }
    //добавить (имя_класса, IS, CLASS)
    add(className, Ontology::IS, Ontology::CLASS);
    //если parentClassName != QString()
    if(parentClassName != QString())
    {
        //добавить (имя_родительского_класса,CONTAINS,имя_класса)
        add(parentClassName, Ontology::CONTAINS, className);
    }
}
