#ifndef ONTOLOGYGENERATOR_H
#define ONTOLOGYGENERATOR_H
#include "OntologyBuilder.h"

class OntologyGenerator : public OntologyBuilder
{
public:
    OntologyGenerator();
    QSet<Triple> generate(const int classCountSummary
                          , const int classPropertiesCount
                          , const int instancesCountSummary
                          , const int classInstancesCount);

    QString generateClass() const;
};

#endif // ONTOLOGYGENERATOR_H
