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
    int exportToCSVBenchmark(const int &size);
    int importFromCSVBenchmark(const int &size);
protected:
    Ontology generate(const int &size);
};

#endif // ONTOLOGYDATABASEBENCHMARK_H
