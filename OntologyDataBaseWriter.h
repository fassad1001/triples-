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

    Ontology importFromCSV(const QString &fileName, const QString ontologyName);
protected:
    void insert_Names(const QSet<QString> &namesToInsert);
    void insert_Triples(QString ontologyID, QSet<Triple> TripleIDs);
    void insert_OntologyNames(const QSet<QString> &namesToInsert);

};

#endif // ONTOLOGYDATABASEWRITER_H
