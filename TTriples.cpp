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

void TTriples::testQhash()
{
    QFETCH(QString, str1);
    QFETCH(QString, str2);
    QFETCH(QString, str3);

    QCOMPARE(qHash(Triple(str1,str2,str3)),qHash(Triple(str1,str2,str3).toString()));
}

void TTriples::testQhash_data()
{
    QTest::addColumn< QString > ("str1");
    QTest::addColumn< QString > ("str2");
    QTest::addColumn< QString > ("str3");

    QTest::newRow("no null") << (QString().append(""))
                          << (QString().append(""))
                             << (QString().append(""));

    QTest::newRow("no null") << (QString().append(""))
                          << (QString().append("2"))
                             << (QString().append("3"));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append(""))
                             << (QString().append("3"));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append("2"))
                             << (QString().append(""));

    QTest::newRow("no null") << (QString().append(""))
                          << (QString().append(""))
                             << (QString().append("3"));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append(""))
                             << (QString().append(""));

    QTest::newRow("no null") << (QString().append("1"))
                          << (QString().append("2"))
                          << (QString().append("3"));
}

void TTriples::testOperatorEquals()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1 == input2,output);
}

void TTriples::testOperatorEquals_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("1 no null no null") << (Triple("1","2","3"))
                                <<(Triple("1","2","3"))
                                  <<(true);

    QTest::newRow("2 null") << (Triple("","",""))
                                <<(Triple("","",""))
                                  <<(true);

    QTest::newRow("3 null no null") << (Triple("","",""))
                                <<(Triple("1","2","3"))
                                  <<(false);

    QTest::newRow("4 no null null") << (Triple("1","2","3"))
                                <<(Triple("","",""))
                                  <<(false);

    QTest::newRow("5 no null no null") << (Triple("1","2","3"))
                                <<(Triple("5","5","5"))
                                  <<(false);

}
