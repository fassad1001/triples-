#ifndef TRIPLE_H

#define TRIPLE_H

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

private:
    QString subject_;
    QString predicate_;
    QString object_;
};

#endif // TRIPLE_H
