#ifndef ONTOLOGYDATABASEWRITER_H

#define ONTOLOGYDATABASEWRITER_H

#include "OntologyDataBaseInterface.h"

#include "Ontology.h"

class OntologyDataBaseWriter : public OntologyDataBaseInterface
{
public:
    OntologyDataBaseWriter(const QString &dataBaseName);

    void writeOntology(const QString &ontologyName, const Ontology &ontology);
    void remove(const QString &ontologyName);
protected:
    QString insert_Names(const QString &nameToInsert);
    QString insert_Triples(const Triple &triple, const QString &ontologyName);
    QString insert_OntologyNames(const QString &nameToInsert);
};

#endif // ONTOLOGYDATABASEWRITER_H
