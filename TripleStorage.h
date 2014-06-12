#ifndef TRIPLESTORAGE_H

#define TRIPLESTORAGE_H

#include "Triple.h"

class TripleStorage
{
public:
    TripleStorage();
    void addTriple(const Triple& triple);
    QSet<QString> objectsFor(const QString &subject, const QString &predicate);
    QSet<QString> subjectsFor(const QString &subject, const QString &predicate);
    QSet<QString> predicatesFor(const QString &subject, const QString &predicate);
private:
    QSet<Triple> triples;
};

#endif // TRIPLESTORAGE_H
