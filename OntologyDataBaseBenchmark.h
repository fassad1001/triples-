#ifndef ONTOLOGYDATABASEBENCHMARK_H

#define ONTOLOGYDATABASEBENCHMARK_H

#include "OntologyBenchmark.h"

#include "OntologyGenerator.h"

#include "OntologyDataBaseReader.h"

#include "OntologyDataBaseWriter.h"

class OntologyDataBaseBenchmark : public OntologyBenchmark
{
public:
    OntologyDataBaseBenchmark();
    int exportToCSVBenchmark(const Ontology &ontology);
    int importFromCSVBenchmark(const Ontology &ontology);
    void commit();
    Ontology generate(const int &size);
protected:
};

#endif // ONTOLOGYDATABASEBENCHMARK_H
