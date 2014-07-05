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
    void TestSubjectAndPredicatesFor_data();
    void TestSubjectAndPredicatesFor();

    void TestPredicatesAndObjects_data();
    void TestPredicatesAndObjects();

    void TestSubjectsAndObjects_data();
    void TestSubjectsAndObjects();

    void TestContains_data();
    void TestContains();

    void TestObjectsFor_data();
    void TestObjectsFor();

    void TestSubjectsFor_data();
    void TestSubjectsFor();

    void TestPredicatesFor_data();
    void TestPredicatesFor();
};

#endif // TTRIPLESTORAGE_H
