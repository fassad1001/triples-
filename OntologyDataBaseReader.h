#ifndef ONTOLOGYDATABASEREADER_H

#define ONTOLOGYDATABASEREADER_H

#include "OntologyDataBaseInterface.h"

#include "Ontology.h"

class OntologyDataBaseReader : public OntologyDataBaseInterface
{
public:
    OntologyDataBaseReader(const QString &dataBaseName);
    Ontology readOntology(const QString &ontologyName);
    QStringList readOntologyName();
};

#endif // ONTOLOGYDATABASEREADER_H
