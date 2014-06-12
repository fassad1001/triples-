#include "Pair.h"

Pair::Pair()
{
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
