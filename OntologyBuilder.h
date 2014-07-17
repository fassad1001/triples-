#ifndef ONTOLOGYBUILDER_H

#define ONTOLOGYBUILDER_H

#include "Ontology.h"

class OntologyBuilder : public Ontology
{
public:
    OntologyBuilder();
    void addClass(const QString &className, const QString &parentClassName = QString());
    Ontology getOntology() const;

};

#endif // ONTOLOGYBUILDER_H
