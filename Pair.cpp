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

bool Pair::operator ==(Pair &p)
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
