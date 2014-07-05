#ifndef TTRIPLES_H

#define TTRIPLES_H

#include <QtTest/QtTest>

#include "Triple.h"

class TTriples : public QObject
{
    Q_OBJECT
public:
    TTriples();
private slots:
    //тесты
    void TestToString_data();
    void TestToString();

    void TestQhash_data();
    void TestQhash();

    void TestOperatorEquals_data();
    void TestOperatorEquals();

    void TestForEqualObjects_data();
    void TestForEqualObjects();

    void TestForEqualSubjects_data();
    void TestForEqualSubjects();

    void TestForEqualPredicates_data();
    void TestForEqualPredicates();

    void TestForEqualBySubjectAndObject_data();
    void TestForEqualBySubjectAndObject();

    void TestForEqualBySubjectsAndPredicates_data();
    void TestForEqualBySubjectsAndPredicates();

    void TestForEqualByObjectsAndPredicates_data();
    void TestForEqualByObjectsAndPredicates();
};

#endif // TTRIPLES_H
