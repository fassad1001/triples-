#include "TripleStorage.h"

TripleStorage::TripleStorage()
{
}

TripleStorage::TripleStorage(const QSet<Triple> &triples) :
    triples_(triples)
{
}

void TripleStorage::addTriple(const Triple &triple)
{
    triples_.insert(triple);
}

QSet<QString> TripleStorage::objectsFor(const QString &subject, const QString &predicate) const
{
    QSet<QString> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsBySubjectAndPredicate(Triple(subject, predicate, "")))
        {
            result<<tr.object();
        }
    }
    return result;
}

QSet<QString> TripleStorage::subjectsFor(const QString &predicate, const QString &object) const
{
    QSet<QString> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsByObjectAndPredicate(Triple("", predicate, object)))
        {
            result<<tr.subject();
        }
    }
    return result;
}

QSet<QString> TripleStorage::predicatesFor(const QString &subject, const QString &object) const
{
    QSet<QString> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsBySubjectAndObject(Triple(subject, "", object)))
        {
            result<<tr.predicate();
        }
    }
    return result;
}

QSet<Pair> TripleStorage::subjectAndPredicatesFor(const QString &object) const
{
    QSet<Pair> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsByObject(Triple("", "", object)))
        {
            result<<Pair(tr.subject(),tr.predicate());
        }
    }
    return result;
}

QSet<Pair> TripleStorage::predicatesAndObjects(const QString &subject) const
{
    QSet<Pair> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsBySubject(Triple(subject, "", "")))
        {
            result << Pair(tr.predicate(),tr.object());
        }
    }
    return result;
}

QSet<Pair> TripleStorage::subjectsAndObjects(const QString &predicate) const
{
    QSet<Pair> result;
    foreach(const Triple tr, triples_)
    {
        if (tr.equalsByPredicate(Triple("",predicate,"")))
        {
            result<<Pair(tr.subject(),tr.object());
        }
    }
    return result;
}

QSet<QString> TripleStorage::traverse(const QString &item, const QString &property, const Direction dir) const
{
    return QSet<QString>();
}

void TripleStorage::remove(const QString &subject, const QString &predicate, const QString object)
{
    triples_.remove(Triple(subject, predicate, object));
}

void TripleStorage::add(const QString &subject, const QString &predicate, const QString object)
{
    triples_.insert(Triple(subject, predicate, object));
}

bool TripleStorage::contains(const Triple &triple) const
{
    return triples_.contains(triple);
}


