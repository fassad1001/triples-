#ifndef ONTOLOGY_H

#define ONTOLOGY_H

#include <QtCore>

#include "TripleStorage.h"

class Ontology : public TripleStorage
{
public:
    const QString IS_VALUE;
    const QString CONTAINS_VALUE;
    const QString CLASS_VALUE;
    Ontology();
    Ontology(QSet<Triple> storage);
    QSet<QString> classInstances(const QString &className) const;
    QSet<QString> anyClassInstances(const QStringList &classNames) const;
    QSet<QString> allClassInstances(const QStringList &classNames) const;
    QSet<QString> allClasses() const;
    QSet<QString> classesForInstance(const QString &instanceName) const;
    QSet<QString> classesForInstances(const QStringList &instanceNames) const;
    QSet<QString> subClasses(const QString &className) const;
    QSet<QString> superClasses(const QString &className) const;
    QSet<QString> mainSuperClass(const QString &instanceName1, const QString &instanceName2) const;
    QSet<QString> mainSuperClass(const QStringList &instances) const;
    bool isValid() const;
    bool isValid(const QSet<QString> checkClasses) const;

};

Q_DECLARE_METATYPE(Ontology)

#endif // ONTOLOGY_H
