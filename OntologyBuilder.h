#ifndef ONTOLOGYBUILDER_H

#define ONTOLOGYBUILDER_H

#include "Ontology.h"

class OntologyBuilder : public Ontology
{
public:
    OntologyBuilder();
    void addClass(const QString &className, const QString &parentClassName = QString());
    void addProperty(const QString &className, const QString &propertyName);
    void addInstance(const QString &className, const QString &instanceName);
    void setPropertyValue(const QString &instanceName, const QString &propertyName, const QString value);

    Ontology getOntology() const;

};

#endif // ONTOLOGYBUILDER_H
