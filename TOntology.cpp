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

void TOntology::TestAllInstances()
{
    QFETCH(Ontology, ontology);

    QFETCH(QSet<QString>, allInstances);

    QCOMPARE(ontology.allInstances(), allInstances);
}

void TOntology::TestAllInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");

    QTest::addColumn <QSet<QString> > ("allInstances");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("cat", Ontology().IS_VALUE,"animal")
                                           <<Triple("dog", Ontology().IS_VALUE,"animal")
                                           <<Triple("animal", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           ))
                                  <<(QSet<QString>()
                                     <<"cat"
                                     <<"dog"
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

void TOntology::TestMainSuperClass()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, instance1);
    QFETCH(QString, instance2);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.mainSuperClass(instance1, instance2), classes);
}

void TOntology::TestMainSuperClass_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("instance1");
    QTest::addColumn <QString> ("instance2");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("a",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("b",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("c",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("d",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("e",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("1",Ontology().IS_VALUE,"f")
                                           <<Triple("2",Ontology().IS_VALUE,"f")
                                           <<Triple("1",Ontology().IS_VALUE,"g")
                                           <<Triple("2",Ontology().IS_VALUE,"g")
                                           ))
                                   <<("1")
                                     <<("2")
                                  <<(QSet<QString>()
                                     <<"f"
                                     );
}

void TOntology::TestMainSuperClass2()
{
    QFETCH(Ontology, ontology);
    QFETCH(QStringList, instances);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.mainSuperClass(instances), classes);
}

void TOntology::TestMainSuperClass2_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QStringList> ("instances");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("a",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("b",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("c",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("d",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("e",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("1",Ontology().IS_VALUE,"f")
                                           <<Triple("2",Ontology().IS_VALUE,"f")
                                           <<Triple("1",Ontology().IS_VALUE,"g")
                                           <<Triple("2",Ontology().IS_VALUE,"g")
                                           ))
                                   <<(QStringList()
                                     <<"1"
                                        <<"2")
                                  <<(QSet<QString>()
                                     <<"f"
                                     );

    QTest::newRow("TestNum2") << (Ontology(QSet<Triple>()
                                           <<Triple("a",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("b",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("c",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("d",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("e",Ontology().CONTAINS_VALUE,"g")
                                           <<Triple("d",Ontology().CONTAINS_VALUE,"f")
                                           <<Triple("1",Ontology().IS_VALUE,"f")
                                           <<Triple("2",Ontology().IS_VALUE,"f")
                                           <<Triple("1",Ontology().IS_VALUE,"g")
                                           <<Triple("2",Ontology().IS_VALUE,"g")
                                           ))
                                   <<(QStringList()
                                     <<"1"
                                        <<"2")
                                  <<(QSet<QString>()
                                     <<"f"
                                     <<"g"
                                     );

}

void TOntology::TestIsValid()
{
    QFETCH(Ontology, ontology);
    QFETCH(bool, isItValid);

    QCOMPARE(ontology.isValid(),isItValid);
}

void TOntology::TestIsValid_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <bool> ("isItValid");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"a")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           ))
                                 <<false;

    QTest::newRow("TestNum2") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("a", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           ))
                                 <<false;

    QTest::newRow("TestNum3") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("a", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"f")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"e")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("e", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("f", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           ))
                                 <<true;

}

void TOntology::TestIsMinimal()
{
    QFETCH(Ontology, ontology);
    QFETCH(bool, isItMinimal);

    QCOMPARE(ontology.isMinimal(),isItMinimal);
}

void TOntology::TestIsMinimal_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <bool> ("isItMinimal");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("a", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("t", Ontology().IS_VALUE, "a")
                                           ))
                                 <<true;

    QTest::newRow("TestNum2") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"f")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("f", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("t", Ontology().IS_VALUE, "b")
                                           << Triple("t", Ontology().IS_VALUE, "f")
                                           ))
                                 <<false;

    QTest::newRow("TestNum3") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"e")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"f")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"g")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"h")
                                           << Triple("e", Ontology().CONTAINS_VALUE,"i")
                                           << Triple("f", Ontology().CONTAINS_VALUE,"j")
                                           << Triple("g", Ontology().CONTAINS_VALUE,"k")
                                           << Triple("h", Ontology().CONTAINS_VALUE,"l")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("e", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("f", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("g", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("h", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("i", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("j", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("k", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("l", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("t", Ontology().IS_VALUE, "i")
                                           << Triple("t", Ontology().IS_VALUE, "j")
                                           ))
                                 <<true;

    QTest::newRow("TestNum3") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"e")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"f")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"g")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"h")
                                           << Triple("e", Ontology().CONTAINS_VALUE,"i")
                                           << Triple("f", Ontology().CONTAINS_VALUE,"j")
                                           << Triple("g", Ontology().CONTAINS_VALUE,"k")
                                           << Triple("h", Ontology().CONTAINS_VALUE,"l")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("e", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("f", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("g", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("h", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("i", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("j", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("k", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("l", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("t", Ontology().IS_VALUE, "i")
                                           << Triple("t", Ontology().IS_VALUE, "j")
                                           << Triple("road", Ontology().IS_VALUE, "b")
                                           ))
                                 <<true;

}

void TOntology::TestMinimalize()
{
    QFETCH(Ontology, ontology1);
    QFETCH(Ontology, ontology2);

    ontology1.minimalize();

    QCOMPARE(ontology1, ontology2);
}

void TOntology::TestMinimalize_data()
{
    QTest::addColumn <Ontology> ("ontology1");
    QTest::addColumn <Ontology> ("ontology2");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           <<Triple("", "", "")
                                           ))
                                 << (Ontology(QSet<Triple>()
                                              <<Triple("", "", "")
                                              ));
}

void TOntology::TestGetNotMinimalInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QSet<QString>, minimalInstances);

    QCOMPARE(ontology.getNotMinimalInstances(), minimalInstances);
}

void TOntology::TestGetNotMinimalInstances_data()
{

    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QSet<QString> > ("minimalInstances");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology().CONTAINS_VALUE,"b")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"c")
                                           << Triple("b", Ontology().CONTAINS_VALUE,"d")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"e")
                                           << Triple("c", Ontology().CONTAINS_VALUE,"f")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"g")
                                           << Triple("d", Ontology().CONTAINS_VALUE,"h")
                                           << Triple("e", Ontology().CONTAINS_VALUE,"i")
                                           << Triple("f", Ontology().CONTAINS_VALUE,"j")
                                           << Triple("g", Ontology().CONTAINS_VALUE,"k")
                                           << Triple("h", Ontology().CONTAINS_VALUE,"l")
                                           << Triple("a", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("b", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("c", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("d", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("e", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("f", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("g", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("h", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("i", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("j", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("k", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("l", Ontology().IS_VALUE, Ontology().CLASS_VALUE)
                                           << Triple("t", Ontology().IS_VALUE, "i")
                                           << Triple("t", Ontology().IS_VALUE, "j")
                                           << Triple("tt", Ontology().IS_VALUE, "i")
                                           << Triple("tt", Ontology().IS_VALUE, "k")
                                           << Triple("wolf", Ontology().IS_VALUE, "j")
                                           ))
                                 << (QSet<QString>());
}


