#ifndef TRIPLESTORAGE_H

#define TRIPLESTORAGE_H

#include "Triple.h"
#include "Pair.h"

enum Direction
{
    TO_SUBJECT,
    TO_OBJECT
};

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

    QSet<QString> traverse(const QString &item,
                           const QString &property,
                           const Direction dir) const;

    void remove(const QString &subject, const QString &predicate, const QString object);
    void add(const QString &subject, const QString &predicate, const QString object);

    bool contains(const Triple &triple) const;

    bool operator ==(const TripleStorage &o) const
    {
        return triples_ == o.triples_;
    }
private:
    QSet<Triple> triples_;
};
Q_DECLARE_METATYPE(TripleStorage)
#endif // TRIPLESTORAGE_H
