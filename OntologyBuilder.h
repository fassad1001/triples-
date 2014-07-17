#ifndef ONTOLOGYBUILDER_H

#define ONTOLOGYBUILDER_H

#include "Ontology.h"

class OntologyBuilder : public Ontology
{
public:
    OntologyBuilder();
    void addClass(const QString &className, const QString &parentClassName = QString());
    void addProperty(const QString &className, const QString &propertyName);

    Ontology getOntology() const;

};

#endif // ONTOLOGYBUILDER_H
