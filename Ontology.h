#ifndef ONTOLOGY_H

#define ONTOLOGY_H

#include <QtCore>

#include "TripleStorage.h"

#include "Class.h"

class Ontology : public TripleStorage
{
public:
    static const QString IS;
    static const QString CONTAINS;
    static const QString CLASS;

    Ontology();
    Ontology(const QSet<Triple> &triples);

    QSet<QString> classInstances(const QString &className) const;
    QSet<QString> anyClassInstances(const QStringList &classNames) const;

    QSet<QString> allClassInstances(const QStringList &classNames) const;
    QSet<QString> allClasses() const;
    QSet<QString> allInstances() const;

    QSet<QString> classesForInstance(const QString &instanceName) const;

    QSet<QString> subClasses(const QString &className) const;
    QSet<QString> superClasses(const QString &className) const;

    QSet<QString> mainSuperClass(const QString &instanceName1, const QString &instanceName2) const;

    bool isValid() const;
    bool isMinimal() const;

    void minimalize();

    bool operator ==(const Ontology &o) const;
};
Q_DECLARE_METATYPE(Ontology)


#endif // ONTOLOGY_H
