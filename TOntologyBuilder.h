#ifndef TONTOLOGYBUILDER_H

#define TONTOLOGYBUILDER_H

#include "OntologyBuilder.h"

#include <QtTest/QtTest>

class TOntologyBuilder : public QObject
{
    Q_OBJECT
public:
    TOntologyBuilder();
private slots:
    void TestAddClass_data();
    void TestAddClass();


};

#endif // TONTOLOGYBUILDER_H
