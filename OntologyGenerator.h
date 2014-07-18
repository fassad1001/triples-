#ifndef ONTOLOGYGENERATOR_H
#define ONTOLOGYGENERATOR_H
#include "OntologyBuilder.h"

class OntologyGenerator : public OntologyBuilder
{
public:
    OntologyGenerator();
    Ontology generate(const int classCountSummary
                          , const int classPropertiesCount
                          , const int instancesCountSummary
                          , const int classInstancesCount);

    QString generateClass() const;
    QString generateInstance() const;
    QString generateProperty() const;
    QString generatePtopertyValue() const;
};

#endif // ONTOLOGYGENERATOR_H
