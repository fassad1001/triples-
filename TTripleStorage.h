#ifndef TTRIPLESTORAGE_H

#define TTRIPLESTORAGE_H

#include <QtTest/QtTest>

#include "TripleStorage.h"

class TTripleStorage : public QObject
{
    Q_OBJECT
public:
    TTripleStorage();
private slots:
    void testSubjectAndPredicatesFor();
    void testSubjectAndPredicatesFor_data();

    void testPredicatesAndObjects();
    void testPredicatesAndObjects_data();

    void testSubjectsAndObjects();
    void testSubjectsAndObjects_data();

    void testContains();
    void testContains_data();

    void testObjectsFor();
    void testObjectsFor_test();

    void testSubjectsFor();
    void testSubjectsFor_test();

    void testPredicatesFor();
    void testPredicatesFor_test();
};

#endif // TTRIPLESTORAGE_H
