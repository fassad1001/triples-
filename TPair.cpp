#include "TPair.h"

TPair::TPair()
{
}

void TPair::TestEquals()
{
    QFETCH(Pair, input1);
    QFETCH(Pair, input2);

    QFETCH(bool, output);

    QCOMPARE(input1 == input2,output);
}

//
void TPair::TestEquals_data()
{
    QTest::addColumn <Pair> ("input1");
    QTest::addColumn <Pair> ("input2");

    QTest::addColumn <bool> ("output");


    QTest::newRow("TestNum1") << (Pair("1", "2"))
                                <<(Pair("1", "2"))
                                  <<(true);

    QTest::newRow("TestNum2") << (Pair("5", "2"))
                                <<(Pair("1", "2"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Pair("", ""))
                                <<(Pair("", ""))
                                  <<(true);

    QTest::newRow("TestNum4") << (Pair("5", ""))
                                <<(Pair("", ""))
                                  <<(false);

    QTest::newRow("TestNum5") << (Pair("5", ""))
                                <<(Pair("5", ""))
                                  <<(true);

    QTest::newRow("TestNum6") << (Pair("", "5"))
                                <<(Pair("", "5"))
                                  <<(true);
}


