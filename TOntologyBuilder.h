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

    void TestAddProperty_data();
    void TestAddProperty();

    void TestAddInstance_data();
    void TestAddInstance();

    void TestSetPropertyValue_data();
    void TestSetPropertyValue();
};

#endif // TONTOLOGYBUILDER_H
