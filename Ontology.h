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
};

Q_DECLARE_METATYPE(Ontology)

#endif // ONTOLOGY_H
