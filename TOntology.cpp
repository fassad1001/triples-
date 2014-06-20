#include "TOntology.h"

TOntology::TOntology()
{
}

void TOntology::TestClassInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);
    
    QFETCH(QSet<QString>, classInstances);

    QCOMPARE(ontology.classInstances(className), classInstances);
}

void TOntology::TestClassInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("classInstances");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"123")
                                           <<Triple("555",Ontology().IS_VALUE,"456")
                                           <<Triple("545",Ontology().IS_VALUE,"456")
                                           ))
                                <<("456")
                                  <<(QSet<QString>()
                                     <<"555"
                                     <<"545"
                                     );

    QTest::newRow("TestNum2") << (Ontology(QSet<Triple>()
                                           <<Triple("",Ontology().IS_VALUE,"")
                                           <<Triple("",Ontology().IS_VALUE,"")
                                           <<Triple("",Ontology().IS_VALUE,"")
                                           ))
                                <<("")
                                  <<(QSet<QString>()
                                     <<""
                                     <<""
                                     <<""
                                     );
}

void TOntology::TestAnyClassInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QStringList, classNames);

    QFETCH(QSet<QString>, classInstances);

    QCOMPARE(ontology.anyClassInstances(classNames), classInstances);
}

void TOntology::TestAnyClassInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QStringList> ("classNames");

    QTest::addColumn <QSet<QString> > ("classInstances");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"123")
                                           <<Triple("555",Ontology().IS_VALUE,"456")
                                           <<Triple("545",Ontology().IS_VALUE,"456")
                                           <<Triple("549",Ontology().IS_VALUE,"457")
                                           ))
                                <<(QStringList()
                                  <<"456"
                                   <<"457"
                                   )
                                  <<(QSet<QString>()
                                     <<"555"
                                     <<"545"
                                     <<"549"
                                     );
}

void TOntology::TestAllClassInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QStringList, classNames);

    QFETCH(QSet<QString>, classInstances);

    QCOMPARE(ontology.anyClassInstances(classNames), classInstances);
}

void TOntology::TestAllClassInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QStringList> ("classNames");

    QTest::addColumn <QSet<QString> > ("classInstances");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"123")
                                           <<Triple("555",Ontology().IS_VALUE,"456")
                                           <<Triple("555",Ontology().IS_VALUE,"456")
                                           <<Triple("555",Ontology().IS_VALUE,"457")
                                           ))
                                <<(QStringList()
                                  <<"456"
                                   <<"457"
                                   )
                                  <<(QSet<QString>()
                                     <<"555"
                                     );
}

void TOntology::TestAllClasses()
{
    QFETCH(Ontology, ontology);

    QFETCH(QSet<QString>, allClasses);

    QCOMPARE(ontology.allClasses(), allClasses);
}

void TOntology::TestAllClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");

    QTest::addColumn <QSet<QString> > ("allClasses");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"catscatscastforcats!")
                                           <<Triple("555",Ontology().IS_VALUE,Ontology().CLASS_VALUE)
                                           <<Triple("555",Ontology().IS_VALUE,Ontology().CLASS_VALUE)
                                           <<Triple("555",Ontology().IS_VALUE,Ontology().CLASS_VALUE)
                                           ))
                                  <<(QSet<QString>()
                                     <<"555"
                                     <<"555"
                                     <<"555"
                                     );
}

void TOntology::TestClassesForInstance()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, instanceName);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.classesForInstance(instanceName), classes);
}

void TOntology::TestClassesForInstance_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("instanceName");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"123")
                                           <<Triple("555",Ontology().IS_VALUE,"556")
                                           <<Triple("555",Ontology().IS_VALUE,"557")
                                           <<Triple("555",Ontology().IS_VALUE,"558")
                                           ))
                                   <<"555"
                                  <<(QSet<QString>()
                                     <<"556"
                                     <<"557"
                                     <<"558"
                                     );
}

void TOntology::TestSubClasses()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);

    QFETCH(QSet<QString>, subClasses);

    QCOMPARE(ontology.subClasses(className), subClasses);
}

void TOntology::TestSubClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("subClasses");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().CONTAINS_VALUE,"123")
                                           <<Triple("555",Ontology().CONTAINS_VALUE,"556")
                                           <<Triple("555",Ontology().CONTAINS_VALUE,"557")
                                           <<Triple("555",Ontology().CONTAINS_VALUE,"558")
                                           ))
                                   <<"555"
                                  <<(QSet<QString>()
                                     <<"556"
                                     <<"557"
                                     <<"558"
                                     );
}

void TOntology::TestSuperClasses()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);

    QFETCH(QSet<QString>, superClasses);

    QCOMPARE(ontology.superClasses(className), superClasses);
}

void TOntology::TestSuperClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("superClasses");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().CONTAINS_VALUE,"123")
                                           <<Triple("556",Ontology().CONTAINS_VALUE,"555")
                                           <<Triple("557",Ontology().CONTAINS_VALUE,"555")
                                           <<Triple("558",Ontology().CONTAINS_VALUE,"555")
                                           ))
                                   <<"555"
                                  <<(QSet<QString>()
                                     <<"556"
                                     <<"557"
                                     <<"558"
                                     );
}

void TOntology::TestClassesForInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QStringList, instanceNames);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.classesForInstances(instanceNames), classes);
}

void TOntology::TestClassesForInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QStringList> ("instanceNames");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("123",Ontology().IS_VALUE,"556")
                                           <<Triple("555",Ontology().IS_VALUE,"556")
                                           <<Triple("555",Ontology().IS_VALUE,"557")
                                           <<Triple("555",Ontology().IS_VALUE,"558")
                                           ))
                                   <<(QStringList()
                                      <<"123"
                                      <<"555"
                                         )
                                  <<(QSet<QString>()
                                     <<"556"
                                     );
}


