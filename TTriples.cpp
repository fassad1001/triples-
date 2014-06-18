#include "TTriples.h"

#include <QtTest/QtTest>

TTriples::TTriples()
{
}

void TTriples::TestToString()
{
    QFETCH(Triple, triple);

    QFETCH(QString, result);

    QCOMPARE(triple.toString(), result);
}

void TTriples::TestToString_data()
{
    QTest::addColumn< Triple > ("triple");

    QTest::addColumn< QString > ("result");

    QTest::newRow("TestNum1") << (Triple("1", "2", "3" ))
                                << ("(1,2,3)");

    QTest::newRow("TestNum2") << (Triple("", "2", "3"))
                                << ("(,2,3)");

    QTest::newRow("TestNum3") << (Triple("1", "", "3"))
                                << ("(1,,3)");

    QTest::newRow("TestNum4") << (Triple("", "", "3"))
                              << ("(,,3)");

    QTest::newRow("TestNum5") << (Triple("1", "", ""))
                              << ("(1,,)");

    QTest::newRow("TestNum6") << (Triple("", "", ""))
                              << ("(,,)");
}

void TTriples::TestQhash()
{
    QFETCH(QString, str1);
    QFETCH(QString, str2);
    QFETCH(QString, str3);

    QCOMPARE(qHash(Triple(str1,str2,str3)),qHash(Triple(str1,str2,str3).toString()));
}

void TTriples::TestQhash_data()
{
    QTest::addColumn< QString > ("str1");
    QTest::addColumn< QString > ("str2");
    QTest::addColumn< QString > ("str3");

    QTest::newRow("TestNum1") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum2") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum3") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum4") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum5") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum6") << ("")
                          << ("")
                             << ("");

    QTest::newRow("TestNum7") << ("")
                          << ("")
                          << ("");
}

void TTriples::TestOperatorEquals()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1 == input2, output);
}

void TTriples::TestOperatorEquals_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("1", "2", "3"))
                                <<(Triple("1", "2", "3"))
                                  <<(true);

    QTest::newRow("TestNum2") << (Triple("", "", ""))
                                <<(Triple("", "", ""))
                                  <<(true);

    QTest::newRow("TestNum3") << (Triple("", "", ""))
                                <<(Triple("1", "2", "3"))
                                  <<(false);

    QTest::newRow("TestNum4") << (Triple("1", "2", "3"))
                                <<(Triple("", "", ""))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("1", "2", "3"))
                                <<(Triple("5", "5", "5"))
                                  <<(false);

}

void TTriples::TestForEqualObjects()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsByObject(input2),output);
}

void TTriples::TestForEqualObjects_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("3","4","5"))
                                <<(Triple("5","5","5"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("3","4","5"))
                                <<(Triple("5","5","6"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("3","4",""))
                                <<(Triple("5","6","5"))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("3","4","5"))
                                <<(Triple("5","6",""))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("3","4",""))
                                <<(Triple("5","6",""))
                                  <<(true);



}

void TTriples::TestForEqualSubjects()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsBySubject(input2), output);
}

void TTriples::TestForEqualSubjects_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("5","4","6"))
                                <<(Triple("5","7","8"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("5","4","6"))
                                <<(Triple("6","7","8"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("5","4","6"))
                                <<(Triple("","7","8"))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("","4","6"))
                                <<(Triple("5","7","8"))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("","4","6"))
                                <<(Triple("","7","8"))
                                  <<(true);
}

void TTriples::TestForEqualPredicates()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsByPredicate(input2),output);
}

void TTriples::TestForEqualPredicates_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("5", "5", "6"))
                                <<(Triple("9", "5", "8"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("5", "4", "6"))
                                <<(Triple("9", "7", "8"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("5", "4", "6"))
                                <<(Triple("9", "", "8"))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("5", "", "6"))
                                <<(Triple("9", "4", "8"))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("5", "", "6"))
                                <<(Triple("5", "", "8"))
                                  <<(true);
}

void TTriples::TestForEqualBySubjectAndObject()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsBySubjectAndObject(input2),output);
}

void TTriples::TestForEqualBySubjectAndObject_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("5", "4", "8"))
                                <<(Triple("5", "7", "8"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("5", "4", "6"))
                                <<(Triple("6", "7", "8"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("5", "4", "6"))
                                <<(Triple("", "7", ""))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("", "4", ""))
                                <<(Triple("5", "7", "8"))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("", "4", ""))
                                <<(Triple("", "7", ""))
                                  <<(true);
}

void TTriples::TestForEqualBySubjectsAndPredicates()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsBySubjectAndPredicate(input2),output);
}

void TTriples::TestForEqualBySubjectsAndPredicates_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("5", "5", "6"))
                                <<(Triple("5", "5", "8"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("5", "4", "6"))
                                <<(Triple("9", "7", "8"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("5", "4", "6"))
                                <<(Triple("", "", "8"))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("", "", "6"))
                                <<(Triple("9", "4", "8"))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("", "", "6"))
                                <<(Triple("", "", "8"))
                                  <<(true);
}

void TTriples::TestForEqualByObjectsAndPredicates()
{
    QFETCH(Triple, input1);
    QFETCH(Triple, input2);

    QFETCH(bool, output);

    QCOMPARE(input1.equalsByObjectAndPredicate(input2),output);
}

void TTriples::TestForEqualByObjectsAndPredicates_data()
{
    QTest::addColumn< Triple > ("input1");
    QTest::addColumn< Triple > ("input2");
    QTest::addColumn< bool > ("output");

    QTest::newRow("TestNum1") << (Triple("5", "5", "6"))
                                <<(Triple("9", "5", "6"))
                                  <<(true);
    QTest::newRow("TestNum2") << (Triple("5", "4", "6"))
                                <<(Triple("9", "7", "8"))
                                  <<(false);

    QTest::newRow("TestNum3") << (Triple("5", "4", "6"))
                                <<(Triple("9", "", ""))
                                  <<(false);
    QTest::newRow("TestNum4") << (Triple("5", "", ""))
                                <<(Triple("9", "4", "8"))
                                  <<(false);

    QTest::newRow("TestNum5") << (Triple("5", "", ""))
                                <<(Triple("9", "", ""))
                                  <<(true);
}
