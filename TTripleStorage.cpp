#include "TTripleStorage.h"

TTripleStorage::TTripleStorage()
{
}

void TTripleStorage::testSubjectAndPredicatesFor()
{


}

void TTripleStorage::testSubjectAndPredicatesFor_data()
{



}

void TTripleStorage::testPredicatesAndObjects()
{

}

void TTripleStorage::testPredicatesAndObjects_data()
{

}

void TTripleStorage::testSubjectsAndObjects()
{

}

void TTripleStorage::testSubjectsAndObjects_data()
{

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

}

void TTripleStorage::testPredicatesFor_data()
{

}
