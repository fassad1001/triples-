#ifndef TRIPLE_H

#define TRIPLE_H

#include "Pair.h"

#include <QtCore>

class Triple
{
public:
    Triple();
    Triple(const QString &subject, const QString &predicate, const QString &object);

    QString subject() const;
    QString predicate() const;
    QString object() const;

    QString toString() const;
    bool operator ==(const Triple &triple) const;

    bool equalsBySubjectAndObject(const Triple &triple);
    bool equalsBySubjectAndPredicate(const Triple &triple);
    bool equalsByObjectAndPredicate(const Triple &triple);

    bool equalsBySubject(const Triple &triple);
    bool equalsByObject(const Triple &triple);
    bool equalsByPredicate(const Triple &triple);

private:
    QString subject_;
    QString predicate_;
    QString object_;
};

Q_DECLARE_METATYPE(Triple)

inline uint qHash(const Triple &triple)
{
    return qHash(triple.toString());
}

#endif // TRIPLE_H
