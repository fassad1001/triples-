#include "TripleStorage.h"

TripleStorage::TripleStorage()
{
}

TripleStorage::TripleStorage(const QSet<Triple> &triples)
{
    triples_ = triples;
}

void TripleStorage::addTriple(const Triple &triple)
{
    triples_.insert(triple);
}

QSet<QString> TripleStorage::objectsFor(const QString &subject, const QString &predicate) const
{
    QSet<QString> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsBySubjectAndPredicate(Triple(subject,predicate,"")))
        {
            result<<tr.object();
        }
    }
    return result;
}

QSet<QString> TripleStorage::subjectsFor(const QString &predicate, const QString &object) const
{
    QSet<QString> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsByObjectAndPredicate(Triple("",predicate,object)))
        {
            result<<tr.subject();
        }
    }
    return result;
}

QSet<QString> TripleStorage::predicatesFor(const QString &subject, const QString &object) const
{
    QSet<QString> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsBySubjectAndObject(Triple(subject,"",object)))
        {
            result<<tr.predicate();
        }
    }
    return result;
}

QSet<Pair> TripleStorage::subjectAndPredicatesFor(const QString &object) const
{
    QSet<Pair> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsByObject(Triple("","",object)))
        {
            result<<Pair(tr.subject(),tr.predicate());
        }
    }
    return result;
}

QSet<Pair> TripleStorage::predicatesAndObjects(const QString &subject) const
{
    QSet<Pair> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsBySubject(Triple(subject,"","")))
        {
            result<<Pair(tr.predicate(),tr.object());
        }
    }
    return result;
}

QSet<Pair> TripleStorage::subjectsAndObjects(const QString &predicate) const
{
    QSet<Pair> result;
    foreach (Triple tr, triples_)
    {
        if (tr.equalsByPredicate(Triple("",predicate,"")))
        {
            result<<Pair(tr.subject(),tr.object());
        }
    }
    return result;
}

bool TripleStorage::contains(const Triple &triple) const
{
    foreach (Triple tr, triples_)
    {
        if (tr == triple)
        {
            return true;
        }
    }
}


