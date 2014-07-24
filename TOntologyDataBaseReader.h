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

};

#endif // TONTOLOGYDATABASEREADER_H
