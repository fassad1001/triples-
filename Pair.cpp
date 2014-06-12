#include "Pair.h"

Pair::Pair()
{
}

Pair::Pair(const QString &first, const QString &second)
{

}

QSet<Pair> Pair::subjectAndPredicatesFor(const QString &object)
{

}

QSet<Pair> Pair::predicatesAndObjects(const QString &object)
{

}

QSet<Pair> Pair::subjectsAndObjects(const QString &object)
{

}

bool Pair::contains(const Triple &triple)
{

}

bool Pair::operator ==(Pair &p)
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
