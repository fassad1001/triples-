#include "Pair.h"

Pair::Pair()
{
}

Pair::Pair(const QString &first, const QString &second) :
   first_(first),
   second_(second)
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

QString Pair::toString() const
{
    return "(" + first_ + "," + second_ + ")";
}

bool Pair::operator ==(const Pair &p) const
{
    return first_ == p.first_ && second_ == p.second_;
}
