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
    void TestClassInstances_data();
    void TestClassInstances();

    void TestAnyClassInstances_data();
    void TestAnyClassInstances();
    
    void TestAllClassInstances_data();
    void TestAllClassInstances();

    void TestAllClasses_data();
    void TestAllClasses();

    void TestAllInstances_data();
    void TestAllInstances();

    void TestClassesForInstance_data();
    void TestClassesForInstance();

    void TestSubClasses_data();
    void TestSubClasses();

    void TestSuperClasses_data();
    void TestSuperClasses();

    void TestMainSuperClass_data();
    void TestMainSuperClass();

    void TestIsValid_data();
    void TestIsValid();

    void TestIsMinimal_data();
    void TestIsMinimal();

    void TestMinimalize_data();
    void TestMinimalize();

    void TestClassProperties_data();
    void TestClassProperties();

    void TestPropertyValues_data();
    void TestPropertyValues();

    void TestInstanceProperties_data();
    void TestInstanceProperties();

    void TestInstancesForProperties_data();
    void TestInstancesForProperties();

    void TestInstancesForNonProperties_data();
    void TestInstancesForNonProperties();
};

#endif // TONTOLOGY_H
