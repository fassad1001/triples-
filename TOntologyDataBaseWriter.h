#ifndef TONTOLOGYDATABASEWRITER_H

#define TONTOLOGYDATABASEWRITER_H

#include "OntologyDataBaseReader.h"

#include "OntologyDataBaseWriter.h"

#include <QtTest/QtTest>

class TOntologyDataBaseWriter: public QObject
{
    Q_OBJECT
public:
    TOntologyDataBaseWriter();
private slots:
    //тесты
    void TestWriteOntology_data();
    void TestWriteOntology();

    void TestRemove_data();
    void TestRemove();
};

#endif // TONTOLOGYDATABASEWRITER_H
