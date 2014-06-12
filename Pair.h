#ifndef PAIR_H
#define PAIR_H
#include <QtCore>
#include "Triple.h"
class Pair
{
public:
    Pair();
    Pair(const QString &first, const QString &second);
    QString first() const;
    QString second() const;

    bool operator ==(Pair &p);

private:
    QString first_;
    QString second_;
};
Q_DECLARE_METATYPE(Pair)
#endif // PAIR_H
