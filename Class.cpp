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

QString Class::toString() const
{
    QString result;
    result << name;
    foreach(QString parent, parents)
    {
        result << ";" << parent;
    }
    return result;
}

bool Class::operator <(const Class &anotherClass) const
{
    if(parents.contains(anotherClass.name))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Class::operator >(const Class &anotherClass) const
{
    if(anotherClass<this)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Class::operator ==(const Class class2) const
{
    if(name == class2.name && parents == class2.parents)
    {
        return true;
    }
    else
    {
        return false;
    }
}
