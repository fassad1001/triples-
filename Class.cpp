#include "Class.h"

Class::Class()
{

}

Class::Class(QString Name,
             QSet<QString> Parents) :
    name(Name),
    parents(Parents)
{

}

bool Class::operator <(const Class &anotherClass) const
{
    if (parents.contains(anotherClass.name))
    {
        return false;
    }
    else
    {
        return true;
    }
}
