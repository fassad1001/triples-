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

    void TestClassesForInstances_data();
    void TestClassesForInstances();

    void TestMainSuperClass_data();
    void TestMainSuperClass();

    void TestMainSuperClass2_data();
    void TestMainSuperClass2();

    void TestIsValid_data();
    void TestIsValid();

    void TestIsMinimal_data();
    void TestIsMinimal();

    void TestGetClassLvl_data();
    void TestGetClassLvl();

    void TestMinimalize_data();
    void TestMinimalize();

    void TestGetNotMinimalInstances_data();
    void TestGetNotMinimalInstances();
};

#endif // TONTOLOGY_H
