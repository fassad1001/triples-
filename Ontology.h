#ifndef ONTOLOGY_H

#define ONTOLOGY_H

#include <QtCore>

#include "TripleStorage.h"

class Ontology : public TripleStorage
{
public:
    static const QString IS;
    static const QString CONTAINS;
    static const QString CLASS;
    Ontology();
    Ontology(QSet<Triple> storage);
    QSet<QString> classInstances(const QString &className) const;
    QSet<QString> anyClassInstances(const QStringList &classNames) const;
    QSet<QString> allClassInstances(const QStringList &classNames) const;
    QSet<QString> allClasses() const;
    QSet<QString> allInstances() const;
    QSet<QString> classesForInstance(const QString &instanceName) const;
    QSet<QString> classesForInstances(const QStringList &instanceNames) const;
    QSet<QString> subClasses(const QString &className) const;
    QSet<QString> superClasses(const QString &className) const;
    QSet<QString> mainSuperClass(const QString &instanceName1, const QString &instanceName2) const;
    QSet<QString> mainSuperClass(const QStringList &instances) const;
    int CompareClassesMainSuper(const QString &className1, const QString &className2) const;
    bool isValid() const;
    bool isValid(const QSet<QString> checkClasses) const;
    bool isMinimal() const;
    bool isMinimalUp(const QString &instance, const QSet<QString> &levelItems) const;
    bool isMinimalDown(const QString &instance, const QSet<QString> &levelItems) const;
    int getClassLvl(const QString &className) const;
    QSet<QString> getNotMinimalInstances() const;
    void minimalize();
    bool operator ==(const Ontology &o) const;

};
Q_DECLARE_METATYPE(Ontology)

#endif // ONTOLOGY_H
