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
    QString toString() const;
    bool operator <(const Class &anotherClass) const;
    bool operator >(const Class &anotherClass) const;
    bool operator ==(const Class class2) const;
};

inline uint qHash(const Class &classs)
{
    return qHash(classs.toString());
}

#endif // CLASS_H
