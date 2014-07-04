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

    void TestAllClasses();
    void TestAllClasses_data();

    void TestAllInstances();
    void TestAllInstances_data();

    void TestClassesForInstance();
    void TestClassesForInstance_data();

    void TestSubClasses();
    void TestSubClasses_data();

    void TestSuperClasses();
    void TestSuperClasses_data();

    void TestClassesForInstances();
    void TestClassesForInstances_data();

    void TestMainSuperClass();
    void TestMainSuperClass_data();

    void TestMainSuperClass2();
    void TestMainSuperClass2_data();

    void TestIsValid();
    void TestIsValid_data();

    void TestIsMinimal();
    void TestIsMinimal_data();

    void TestGetClassLvl_data();
    void TestGetClassLvl();

    void TestMinimalize();
    void TestMinimalize_data();

    void TestGetNotMinimalInstances();
    void TestGetNotMinimalInstances_data();
};

#endif // TONTOLOGY_H
