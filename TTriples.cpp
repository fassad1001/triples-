#include "TTriples.h"

#include "Triple.h"
#include <QtTest/QtTest>

TTriples::TTriples()
{
}

void TTriples::testToString()
{
    QFETCH(QString, str1);
    QFETCH(QString, str2);
    QFETCH(QString, str3);

    QFETCH(QString, output);

    QCOMPARE(Triple(str1,str2,str3).toString(), output);
}

void TTriples::testToString_data()
{
    QTest::addColumn< QString > ("str1");
    QTest::addColumn< QString > ("str2");
    QTest::addColumn< QString > ("str3");

    QTest::addColumn< QString > ("output");

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append("2"))
                             << (QString().append("3"))
                                << (QString().append("(1,2,3)"));

    QTest::newRow("no null") << (QString().append(""))
                          << (QString().append("2"))
                             << (QString().append("3"))
                                << (QString().append("(,2,3)"));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append(""))
                             << (QString().append("3"))
                                << (QString().append("(1,,3)"));

    QTest::newRow("no null") << (QString().append(""))
                          << (QString().append(""))
                             << (QString().append("3"))
                                << (QString().append("(,,3)"));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append(""))
                             << (QString().append(""))
                                << (QString().append("(1,,)"));

    QTest::newRow("null") << (QString().append(""))
                          << (QString().append(""))
                             << (QString().append(""))
                                << (QString().append("(,,)"));
}
