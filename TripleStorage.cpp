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

QSet<QString> TripleStorage::objectsFor(const QString &subject, const QString &predicate)
{

}

QSet<QString> TripleStorage::subjectsFor(const QString &subject, const QString &predicate)
{

}

QSet<QString> TripleStorage::predicatesFor(const QString &subject, const QString &predicate)
{

}
