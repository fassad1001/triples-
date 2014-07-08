#ifndef CLASS_H

#define CLASS_H

#include <QtCore>

class Class
{
public:
    QString name;
    QSet<QString> parents;
    Class();
    Class(QString Name, QSet<QString> Parents);
    bool operator <(const Class &anotherClass) const;
    bool operator >(const Class &anotherClass) const;
};

#endif // CLASS_H
