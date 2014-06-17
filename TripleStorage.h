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
    QSet<QString> subjectsFor(const QString &predicate, const QString &object);
    QSet<QString> predicatesFor(const QString &object, const QString &subject);

    QSet<Pair> subjectAndPredicatesFor(const QString &object);
    QSet<Pair> predicatesAndObjects(const QString &subject);
    QSet<Pair> subjectsAndObjects(const QString &predicate);

    bool contains(const Triple &triple);
private:
    QSet<Triple> triples_;
};
Q_DECLARE_METATYPE(TripleStorage)
#endif // TRIPLESTORAGE_H
