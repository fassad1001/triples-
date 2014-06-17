#include "TTripleStorage.h"

TTripleStorage::TTripleStorage()
{

}

void TTripleStorage::testSubjectAndPredicatesFor()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);

    QFETCH(QSet<Pair>, output);

    QCOMPARE(input0.subjectAndPredicatesFor(input1),output);
}

void TTripleStorage::testSubjectAndPredicatesFor_data()
{
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QSet<Pair> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                              <<(QSet<Pair>()
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("5")
                                              <<(QSet<Pair>()
                                                 <<Pair("1","2")
                                                 <<Pair("3","4")
                                                 <<Pair("5","6")
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","4")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("5","4","4")
                                        <<Triple("4","5","4")))
                                          <<("5")
                                              <<(QSet<Pair>()
                                                 <<Pair("1","2")
                                                 <<Pair("3","4")
                                                 <<Pair("5","6")
                                                 );

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","4")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("5","4","4")
                                        <<Triple("4","5","4")))
                                          <<("15")
                                              <<(QSet<Pair>()
                                                 );

}

void TTripleStorage::testPredicatesAndObjects()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);

    QFETCH(QSet<Pair>, output);

    QCOMPARE(input0.predicatesAndObjects(input1),output);
}

void TTripleStorage::testPredicatesAndObjects_data()
{
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QSet<Pair> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                              <<(QSet<Pair>()
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("5","5","5")
                                        <<Triple("5","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("5")
                                              <<(QSet<Pair>()
                                                 <<Pair("5","5")
                                                 <<Pair("4","5")
                                                 <<Pair("6","5")
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","4")
                                        <<Triple("15","2","5")
                                        <<Triple("15","4","5")
                                        <<Triple("15","6","5")
                                        <<Triple("5","4","4")
                                        <<Triple("4","5","4")))
                                          <<("15")
                                              <<(QSet<Pair>()
                                                 <<Pair("2","5")
                                                 <<Pair("4","5")
                                                 <<Pair("6","5")
                                                 );

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","4")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("5","4","4")
                                        <<Triple("4","5","4")))
                                          <<("15")
                                              <<(QSet<Pair>()
                                                 );

}

void TTripleStorage::testSubjectsAndObjects()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);

    QFETCH(QSet<Pair>, output);

    QCOMPARE(input0.subjectsAndObjects(input1),output);
}

void TTripleStorage::testSubjectsAndObjects_data()
{
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QSet<Pair> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                              <<(QSet<Pair>()
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 <<Pair("","")
                                                 );

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("5","5","5")
                                        <<Triple("4","5","5")
                                        <<Triple("6","5","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("5")
                                              <<(QSet<Pair>()
                                                 <<Pair("5","5")
                                                 <<Pair("4","5")
                                                 <<Pair("6","5")
                                                 );

    QTest::newRow("not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","4","4")
                                        <<Triple("2","15","5")
                                        <<Triple("4","15","5")
                                        <<Triple("6","15","5")
                                        <<Triple("4","4","4")
                                        <<Triple("5","5","4")))
                                          <<("15")
                                              <<(QSet<Pair>()
                                                 <<Pair("2","5")
                                                 <<Pair("4","5")
                                                 <<Pair("6","5")
                                                 );

    QTest::newRow("blank = false") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("blank & not blank = false") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("1","2","5")
                                        <<Triple("3","5","5")
                                        <<Triple("5","6","5")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("not blank = false") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","4")
                                        <<Triple("1","2","5")
                                        <<Triple("3","4","5")
                                        <<Triple("5","6","5")
                                        <<Triple("5","4","4")
                                        <<Triple("4","5","4")))
                                          <<("15")
                                              <<(QSet<Pair>()
                                                 );
}

void TTripleStorage::testContains()
{

}

void TTripleStorage::testContains_data()
{

}

void TTripleStorage::testObjectsFor()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);
    QFETCH(QString, input2);

    QFETCH(QSet<QString>, output);

    QCOMPARE(input0.objectsFor(input1,input2),output);
}

void TTripleStorage::testObjectsFor_data()
{
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QString> ("input2");

    QTest::addColumn <QSet<QString> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                            <<("")
                                              <<(QSet<QString>()
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<"");

    QTest::newRow("not blank = false") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","5","1")
                                        <<Triple("5","5","2")
                                        <<Triple("5","5","3")
                                        <<Triple("5","5","4")
                                        <<Triple("5","5","5")
                                        ))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"1"
                                                 <<"2"
                                                 <<"3"
                                                 <<"4"
                                                 <<"5");

    QTest::newRow("not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","5","5")
                                        <<Triple("2","5","5")
                                        <<Triple("3","5","5")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        ))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"5");

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","","5")
                                        <<Triple("2","5","")
                                        <<Triple("3","5","5")
                                        <<Triple("","5","5")
                                        <<Triple("5","5","5")
                                        ))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"5");

    QTest::newRow("blank & not blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","","5")
                                        <<Triple("2","5","")
                                        <<Triple("3","5","5")
                                        <<Triple("","5","5")
                                        <<Triple("5","5","5")
                                        ))
                                          <<("4")
                                            <<("5")
                                              <<(QSet<QString>());
}

void TTripleStorage::testSubjectsFor()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);
    QFETCH(QString, input2);

    QFETCH(QSet<QString>, output);

    QCOMPARE(input0.subjectsFor(input1,input2),output);
}

void TTripleStorage::testSubjectsFor_data()
{   
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QString> ("input2");
    QTest::addColumn <QSet<QString> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                            <<("")
                                              <<(QSet<QString>()
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<"");
    
    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","","")
                                        <<Triple("2","","")
                                        <<Triple("3","","")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","","")))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"4"
                                                 <<"5");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","5","5")
                                        <<Triple("2","4","4")
                                        <<Triple("3","4","4")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","5","5")))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"1"
                                                 <<"4"
                                                 <<"5"
                                                 <<"6");
    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","","")
                                        <<Triple("2","","")
                                        <<Triple("3","","")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","","")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","5","5")
                                        <<Triple("2","4","4")
                                        <<Triple("3","4","4")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","5","5")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());

}

void TTripleStorage::testPredicatesFor()
{
    QFETCH(TripleStorage, input0);
    QFETCH(QString, input1);
    QFETCH(QString, input2);

    QFETCH(QSet<QString>, output);

    QCOMPARE(input0.predicatesFor(input1,input2),output);
}

void TTripleStorage::testPredicatesFor_data()
{
    QTest::addColumn <TripleStorage> ("input0");
    QTest::addColumn <QString> ("input1");
    QTest::addColumn <QString> ("input2");
    QTest::addColumn <QSet<QString> > ("output");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("")
                                            <<("")
                                              <<(QSet<QString>()
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<""
                                                 <<"");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("4","","5")
                                        <<Triple("4","","5")
                                        <<Triple("4","","5")
                                        <<Triple("5","4","5")
                                        <<Triple("5","5","5")
                                        <<Triple("5","","4")))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"4"
                                                 <<"5");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("5","1","5")
                                        <<Triple("5","4","5")
                                        <<Triple("5","5","5")
                                        <<Triple("5","6","5")
                                        <<Triple("4","0","5")
                                        <<Triple("5","0","4")))
                                          <<("5")
                                            <<("5")
                                              <<(QSet<QString>()
                                                 <<"1"
                                                 <<"4"
                                                 <<"5"
                                                 <<"6");

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")
                                        <<Triple("","","")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","","")
                                        <<Triple("2","","")
                                        <<Triple("3","","")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","","")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());

    QTest::newRow("blank = true") << (TripleStorage(QSet<Triple>()
                                        <<Triple("1","5","5")
                                        <<Triple("2","4","4")
                                        <<Triple("3","4","4")
                                        <<Triple("4","5","5")
                                        <<Triple("5","5","5")
                                        <<Triple("6","5","5")))
                                          <<("9")
                                            <<("9")
                                              <<(QSet<QString>());
}
