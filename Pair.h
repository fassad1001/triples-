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
    bool operator ==(Pair &p)
    {
        if (first_ == p.first_ && second_ == p.second_)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

private:
    QString first_;
    QString second_;
};

#endif // PAIR_H
