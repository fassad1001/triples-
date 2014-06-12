#ifndef TPAIR_H

#define TPAIR_H

#include "Pair.h"

#include <QtTest/QtTest>

class TPair: public QObject
{
    Q_OBJECT
public:
    TPair();
private slots:
    //тесты
    void testSubjectAndPredicatesFor();
    void testSubjectAndPredicatesFor_data();

    void testPredicatesAndObjects();
    void testPredicatesAndObjects_data();

    void testSubjectsAndObjects();
    void testSubjectsAndObjects_data();

    void testContains();
    void testContains_data();
};

#endif // TPAIR_H
