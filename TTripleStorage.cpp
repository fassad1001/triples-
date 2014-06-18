#include "TTripleStorage.h"

TTripleStorage::TTripleStorage()
{

}

void TTripleStorage::TestSubjectAndPredicatesFor()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring);

    QFETCH(QSet<Pair>, qset);

    QCOMPARE(storage.subjectAndPredicatesFor(qstring),qset);
}

void TTripleStorage::TestSubjectAndPredicatesFor_data()
{
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring");
    QTest::addColumn <QSet<Pair> > ("qset");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")))
                                  <<("4")
                                 <<(QSet<Pair>()
                                    );

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
                                                                <<Triple("","","")
                                                                <<Triple("1","2","5")
                                                                <<Triple("3","4","5")
                                                                <<Triple("5","6","5")
                                                                <<Triple("","","")
                                                                <<Triple("","","")))
                                              <<("4")
                                             <<(QSet<Pair>()
                                                );

    QTest::newRow("TestNum6") << (TripleStorage(QSet<Triple>()
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

void TTripleStorage::TestPredicatesAndObjects()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring);

    QFETCH(QSet<Pair>, qset);

    QCOMPARE(storage.predicatesAndObjects(qstring),qset);
}

void TTripleStorage::TestPredicatesAndObjects_data()
{
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring");
    QTest::addColumn <QSet<Pair> > ("qset");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")))
                                  <<("4")
                                 <<(QSet<Pair>()
                                    );

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
                                                                <<Triple("","","")
                                                                <<Triple("1","2","5")
                                                                <<Triple("3","4","5")
                                                                <<Triple("5","6","5")
                                                                <<Triple("","","")
                                                                <<Triple("","","")))
                                              <<("4")
                                             <<(QSet<Pair>()
                                                );

    QTest::newRow("TestNum6") << (TripleStorage(QSet<Triple>()
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

void TTripleStorage::TestSubjectsAndObjects()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring);

    QFETCH(QSet<Pair>, qset);

    QCOMPARE(storage.subjectsAndObjects(qstring),qset);
}

void TTripleStorage::TestSubjectsAndObjects_data()
{

    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring");
    QTest::addColumn <QSet<Pair> > ("qset");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
                                                     <<Triple("","","")
                                                     <<Triple("","","")
                                                     <<Triple("","","")
                                                     <<Triple("","","")
                                                     <<Triple("","","")
                                                     <<Triple("","","")))
                                   <<("4")
                                  <<(QSet<Pair>()
                                     );

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
                                                                 <<Triple("","","")
                                                                 <<Triple("1","2","5")
                                                                 <<Triple("3","5","5")
                                                                 <<Triple("5","6","5")
                                                                 <<Triple("","","")
                                                                 <<Triple("","","")))
                                               <<("4")
                                              <<(QSet<Pair>()
                                                 );

    QTest::newRow("TestNum6") << (TripleStorage(QSet<Triple>()
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

void TTripleStorage::TestContains()
{
    QFETCH(TripleStorage, storage);
    QFETCH(Triple, triple);

    QFETCH(bool, result);

    QCOMPARE(storage.contains(triple),result);
}

void TTripleStorage::TestContains_data()
{
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <Triple> ("triple");
    QTest::addColumn <bool > ("result");

        QTest::newRow("TestNum1")<<(TripleStorage(QSet<Triple>()
                                          <<Triple("5","5","5")
                                          <<Triple("5","5","4")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")))
                        <<(Triple("5","5","5"))
                       <<(true);

        QTest::newRow("TestNum2")<<(TripleStorage(QSet<Triple>()
                                          <<Triple("5","5","5")
                                          <<Triple("5","5","4")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")))
                        <<(Triple("3","4","3"))
                       <<(false);

        QTest::newRow("TestNum3")<<(TripleStorage(QSet<Triple>()
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")
                                          <<Triple("","","")))
                        <<(Triple("","",""))
                       <<(true);
}

void TTripleStorage::TestObjectsFor()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring1);
    QFETCH(QString, qstring2);

    QFETCH(QSet<QString>, result);

    QCOMPARE(storage.objectsFor(qstring1,qstring2), result);
}

void TTripleStorage::TestObjectsFor_data()
{
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring1");
    QTest::addColumn <QString> ("qstring2");

    QTest::addColumn <QSet<QString> > ("result");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("", "", "")
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

    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
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

void TTripleStorage::TestSubjectsFor()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring1);
    QFETCH(QString, qstring2);

    QFETCH(QSet<QString>, result);

    QCOMPARE(storage.subjectsFor(qstring1,qstring2),result);
}

void TTripleStorage::TestSubjectsFor_data()
{   
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring1");
    QTest::addColumn <QString> ("qstring2");
    QTest::addColumn <QSet<QString> > ("result");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
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
    
    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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
    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")))
                                  <<("9")
                                 <<("9")
                                <<(QSet<QString>());

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("1","","")
                                                    <<Triple("2","","")
                                                    <<Triple("3","","")
                                                    <<Triple("4","5","5")
                                                    <<Triple("5","5","5")
                                                    <<Triple("6","","")))
                                  <<("9")
                                 <<("9")
                                <<(QSet<QString>());

    QTest::newRow("TestNum6") << (TripleStorage(QSet<Triple>()
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

void TTripleStorage::TestPredicatesFor()
{
    QFETCH(TripleStorage, storage);
    QFETCH(QString, qstring1);
    QFETCH(QString, qstring2);

    QFETCH(QSet<QString>, result);

    QCOMPARE(storage.predicatesFor(qstring1,qstring2),result);
}

void TTripleStorage::TestPredicatesFor_data()
{
    QTest::addColumn <TripleStorage> ("storage");
    QTest::addColumn <QString> ("qstring1");
    QTest::addColumn <QString> ("qstring2");
    QTest::addColumn <QSet<QString> > ("result");

    QTest::newRow("TestNum1") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum2") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum3") << (TripleStorage(QSet<Triple>()
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

    QTest::newRow("TestNum4") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")
                                                    <<Triple("","","")))
                                  <<("9")
                                 <<("9")
                                <<(QSet<QString>());

    QTest::newRow("TestNum5") << (TripleStorage(QSet<Triple>()
                                                    <<Triple("1","","")
                                                    <<Triple("2","","")
                                                    <<Triple("3","","")
                                                    <<Triple("4","5","5")
                                                    <<Triple("5","5","5")
                                                    <<Triple("6","","")))
                                  <<("9")
                                 <<("9")
                                <<(QSet<QString>());

    QTest::newRow("TestNum6") << (TripleStorage(QSet<Triple>()
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
