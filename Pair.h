#ifndef PAIR_H

#define PAIR_H

#include <QtCore>

class Pair
{
public:
    Pair();
    Pair(const QString &first, const QString &second);
    QString first() const;
    QString second() const;

    QString toString() const;

    bool operator ==(const Pair &p) const;

private:
    QString first_;
    QString second_;
};


inline uint qHash(const Pair &pair)
{
    return qHash(pair.toString());
}


Q_DECLARE_METATYPE(Pair)
#endif // PAIR_H
