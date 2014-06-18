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
    void TestToString();
    void TestToString_data();

    void TestQhash();
    void TestQhash_data();

    void TestOperatorEquals();
    void TestOperatorEquals_data();

    void TestForEqualObjects();
    void TestForEqualObjects_data();

    void TestForEqualSubjects();
    void TestForEqualSubjects_data();

    void TestForEqualPredicates();
    void TestForEqualPredicates_data();

    void TestForEqualBySubjectAndObject();
    void TestForEqualBySubjectAndObject_data();

    void TestForEqualBySubjectsAndPredicates();
    void TestForEqualBySubjectsAndPredicates_data();

    void TestForEqualByObjectsAndPredicates();
    void TestForEqualByObjectsAndPredicates_data();
};

#endif // TTRIPLES_H
