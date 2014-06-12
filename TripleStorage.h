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

    QSet<QString> objectsFor(const QString &subject, const QString &predicate);
    QSet<QString> subjectsFor(const QString &subject, const QString &predicate);
    QSet<QString> predicatesFor(const QString &subject, const QString &predicate);

    QSet<Pair> subjectAndPredicatesFor(const QString &object);
    QSet<Pair> predicatesAndObjects(const QString &object);
    QSet<Pair> subjectsAndObjects(const QString &object);

    bool contains(const Triple &triple);
private:
    QSet<Triple> triples_;
};
Q_DECLARE_METATYPE(TripleStorage)
#endif // TRIPLESTORAGE_H
