#ifndef PAIR_H
#define PAIR_H
#include <QtCore>
#include "Triple.h"
class Pair
{
public:
    Pair();
    Pair(const QString &first, const QString &second);
    QSet<Pair> subjectAndPredicatesFor(const QString &object);
    QSet<Pair> predicatesAndObjects(const QString &object);
    QSet<Pair> subjectsAndObjects(const QString &object);
    bool contains(const Triple &triple);
    bool operator ==(Pair &p);

private:
    QString first_;
    QString second_;
};

#endif // PAIR_H
