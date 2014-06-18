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
    void TestSubjectAndPredicatesFor();
    void TestSubjectAndPredicatesFor_data();

    void TestPredicatesAndObjects();
    void TestPredicatesAndObjects_data();

    void TestSubjectsAndObjects();
    void TestSubjectsAndObjects_data();

    void TestContains();
    void TestContains_data();

    void TestObjectsFor();
    void TestObjectsFor_data();

    void TestSubjectsFor();
    void TestSubjectsFor_data();

    void TestPredicatesFor();
    void TestPredicatesFor_data();
};

#endif // TTRIPLESTORAGE_H
