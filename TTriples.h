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
    void testToString();
    void testToString_data();

    void testQhash();
    void testQhash_data();

    void testOperatorEquals();
    void testOperatorEquals_data();

    void testForEqualObjects();
    void testForEqualObjects_data();

    void testForEqualSubjects();
    void testForEqualSubjects_data();

    void testForEqualPredicates();
    void testForEqualPredicates_data();

    void testForEqualBySubjectAndObject();
    void testForEqualBySubjectAndObject_data();

    void testForEqualBySubjectsAndPredicates();
    void testForEqualBySubjectsAndPredicates_data();

    void testForEqualByObjectsAndPredicates();
    void testForEqualByObjectsAndPredicates_data();
};

#endif // TTRIPLES_H
