#ifndef TONTOLOGYDATABASEREADER_H

#define TONTOLOGYDATABASEREADER_H

#include "OntologyDataBaseReader.h"

#include "OntologyDataBaseWriter.h"

#include <QtTest/QtTest>

class TOntologyDataBaseReader: public QObject
{
    Q_OBJECT
public:
    TOntologyDataBaseReader();
private slots:
    //тесты
    void TestReadOntology_data();
    void TestReadOntology();

    void TestImportCSV_data();
    void TestImportCSV();
};

#endif // TONTOLOGYDATABASEREADER_H
