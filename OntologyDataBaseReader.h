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

    void exportToCSV(const QString &fileName,
                     const QString &ontologyName,
                     const QHash<QString, QString> SystemValueUserValue = systemValueUserValue);

};
QHash<QString, QString> hash;
QHash<QString, QString> OntologyDataBaseInterface::systemValueUserValue = hash.insert(Ontology::CLASS, Ontology::CLASS)
        .insert(Ontology::CONTAINS, Ontology::CONTAINS)
        .insert(Ontology::HAS_PROPERTY, Ontology::HAS_PROPERTY)
        .insert(Ontology::IS, Ontology::IS);
#endif // ONTOLOGYDATABASEREADER_H
