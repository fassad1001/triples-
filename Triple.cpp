#include "Triple.h"

Triple::Triple()
{

}

Triple::Triple(const QString &subject,
               const QString &predicate,
               const QString &object) :
    subject_(subject),
    predicate_(predicate),
    object_(object)
{
}

QString Triple::subject() const
{
   return subject_;
}

QString Triple::predicate() const
{
   return predicate_;
}

QString Triple::object() const
{
    return object_;
}

QString Triple::toString() const
{
    QString result;
    result.append("(").append(this->subject()).append(",").append(this->predicate()).append(",").append(this->object()).append(")");
    return result;
}

bool Triple::operator ==(const Triple &t)
{
    if (subject()==t.subject()&&predicate()==t.predicate()&&object()==t.object())
    {
        return true;
    }
    else
    {
        return false;
    }
}
