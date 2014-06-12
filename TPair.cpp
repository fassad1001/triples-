#include "TPair.h"

TPair::TPair()
{
}

void TPair::testEquals()
{
    QFETCH(Pair, input1);
    QFETCH(Pair, input2);

    QFETCH(bool, output);

    QCOMPARE(input1 == input2,output);
}

void TPair::testEquals_data()
{
    QTest::addColumn <Pair> ("input1");
    QTest::addColumn <Pair> ("input2");

    QTest::addColumn <bool> ("output");


    QTest::newRow("1 no null no null") << (Pair("1","2"))
                                <<(Pair("1","2"))
                                  <<(true);

    QTest::newRow("1 no null no null") << (Pair("5","2"))
                                <<(Pair("1","2"))
                                  <<(false);

    QTest::newRow("1 no null no null") << (Pair("",""))
                                <<(Pair("",""))
                                  <<(true);

    QTest::newRow("1 no null no null") << (Pair("5",""))
                                <<(Pair("",""))
                                  <<(false);

    QTest::newRow("1 no null no null") << (Pair("5",""))
                                <<(Pair("5",""))
                                  <<(true);

    QTest::newRow("1 no null no null") << (Pair("","5"))
                                <<(Pair("","5"))
                                  <<(true);
}


