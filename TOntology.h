#ifndef TONTOLOGY_H

#define TONTOLOGY_H

#include "Ontology.h"

#include <QtTest/QtTest>

class TOntology : public QObject
{
    Q_OBJECT
public:
    TOntology();
private slots: 
    //функции тестирования
    void TestClassInstances();
    void TestClassInstances_data();
    
    void TestAnyClassInstances();
    void TestAnyClassInstances_data();
    
    void TestAllClassInstances();
    void TestAllClassInstances_data();
};

#endif // TONTOLOGY_H
