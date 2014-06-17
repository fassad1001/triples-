#include "Pair.h"

Pair::Pair()
{
}

Pair::Pair(const QString &first, const QString &second)
{
    first_=first;
    second_=second;
}

QString Pair::first() const
{
    return first_;
}

QString Pair::second() const
{
    return second_;
}

QString Pair::toString() const
{
    return QString ("(")+first_+","+second_+")";
}

bool Pair::operator ==(const Pair &p) const
{
    if (first() == p.first() && second() == p.second())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
