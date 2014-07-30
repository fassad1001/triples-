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
    void insert_Names(const QString &nameToInsert);
    void insert_Triples(const int &subjectID,
                           const int &predicateID, const int &objectID,
                           const int &ontologyID);
    void insert_OntologyNames(const QString &nameToInsert);

};

#endif // ONTOLOGYDATABASEWRITER_H
