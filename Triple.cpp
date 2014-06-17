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
    return QString("(") + subject_ + "," + predicate_ + "," + object_ + ")";
}

bool Triple::operator ==(const Triple &triple) const
{
    return subject_ == triple.subject_
            && predicate_== triple.predicate_
            && object_ == triple.object_;
}

bool Triple::equalsBySubjectAndObject(const Triple &triple)
{
    return subject_ == triple.subject_
            && object_ == triple.object();
}

bool Triple::equalsBySubjectAndPredicate(const Triple &triple)
{
    return subject_ == triple.subject_
            && predicate_== triple.predicate_;
}

bool Triple::equalsByObjectAndPredicate(const Triple &triple)
{
    return predicate_== triple.predicate_
            && object_ == triple.object_;
}

bool Triple::equalsBySubject(const Triple &triple)
{
    return subject_ == triple.subject_;
}

bool Triple::equalsByObject(const Triple &triple)
{
    return object_ == triple.object_;
}

bool Triple::equalsByPredicate(const Triple &triple)
{
    return predicate_== triple.predicate_;
}

