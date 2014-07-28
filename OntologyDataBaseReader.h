#ifndef ONTOLOGYDATABASEREADER_H

#define ONTOLOGYDATABASEREADER_H

#include "OntologyDataBaseInterface.h"

#include "OntologyDataBaseWriter.h"

#include "Ontology.h"

class OntologyDataBaseReader : public OntologyDataBaseInterface
{
public:
    OntologyDataBaseReader(const QString &dataBaseName);

    Ontology readOntology(const QString &ontologyName);

    void exportToCSV(const QString &fileName, const QString &ontologyName);

    void importFromCSV(const QString &fileName, const QString &ontologyName);

};

#endif // ONTOLOGYDATABASEREADER_H
