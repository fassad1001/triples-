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

bool Triple::equalsBySubjectAndObject(const Triple &triple) const
{
    return subject_ == triple.subject_
            && object_ == triple.object_;
}

bool Triple::equalsBySubjectAndPredicate(const Triple &triple) const
{
    return subject_ == triple.subject_
            && predicate_== triple.predicate_;
}

bool Triple::equalsByObjectAndPredicate(const Triple &triple) const
{
    return predicate_== triple.predicate_
            && object_ == triple.object_;
}

bool Triple::equalsBySubject(const Triple &triple) const
{
    return subject_ == triple.subject_;
}

bool Triple::equalsByObject(const Triple &triple) const
{
    return object_ == triple.object_;
}

bool Triple::equalsByPredicate(const Triple &triple) const
{
    return predicate_== triple.predicate_;
}

Triple Triple::random(const int maxValue)
{
    const int subject = qrand() % maxValue;
    const int predicate = qrand() % maxValue;
    const int object = qrand() % maxValue;
    return Triple(QString::number(subject), QString::number(predicate), QString::number(object));
}

QSet<Triple> Triple::randoms(const int number, const int maxValue)
{
    QSet<Triple> triples;
    for (int i = 0; i<=number; i++)
    {
        triples << random(maxValue);
    }
    return triples;
}

