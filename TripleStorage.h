#ifndef TRIPLESTORAGE_H

#define TRIPLESTORAGE_H


#include "Triple.h"

#include "Pair.h"

class TripleStorage
{
public:
    TripleStorage();
    TripleStorage(const QSet<Triple> &triples);

    void addTriple(const Triple &triple);

    QSet<QString> objectsFor(const QString &subject, const QString &predicate) const;
    QSet<QString> subjectsFor(const QString &predicate, const QString &object) const;
    QSet<QString> predicatesFor(const QString &subject, const QString &object) const;

    QSet<Pair> subjectAndPredicatesFor(const QString &object) const;
    QSet<Pair> predicatesAndObjects(const QString &subject) const;
    QSet<Pair> subjectsAndObjects(const QString &predicate) const;

    bool contains(const Triple &triple) const;
protected:
    QSet<Triple> triples_;
};
Q_DECLARE_METATYPE(TripleStorage)
#endif // TRIPLESTORAGE_H
