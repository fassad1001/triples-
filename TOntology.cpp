#include "TOntology.h"

TOntology::TOntology()
{
}

void TOntology::TestClassInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("classInstances");

    QTest::newRow("blank-ontology") << (Ontology(QSet<Triple>()))
                                    <<("class123")
                                   <<(QSet<QString>());

    QTest::newRow("class-without-instances") << (Ontology(QSet<Triple>()
                                                          << Triple("class1", Ontology::IS, Ontology::CLASS)))
                                             <<("class1")
                                            <<(QSet<QString>());

    QTest::newRow("class-with-1-instance") << (Ontology(QSet<Triple>()
                                                        << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                        << Triple("instance1", Ontology::IS, "class1")))
                                           <<("class1")
                                          <<(QSet<QString>()
                                             <<"instance1");

    QTest::newRow("fake-class-query") << (Ontology(QSet<Triple>()
                                                   << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                   << Triple("instance1", Ontology::IS, "class1")))
                                      <<("class2")
                                     <<(QSet<QString>());

    QTest::newRow("two-instances-with-inheritance") << (Ontology(QSet<Triple>()
                                                                 << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                 << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                 << Triple("class1", Ontology::CONTAINS, "class2")
                                                                 << Triple("instance1", Ontology::IS,"class2")
                                                                 << Triple("instance2", Ontology::IS,"class2")))
                                                    <<("class1")
                                                   <<(QSet<QString>()
                                                      << "instance1"
                                                      << "instance2");
    //запрос к пустой онтологии;класс без экземпляров; класс с одним экземляров; запрос для класса, отсутсвующего в онтологии; запрос для класса, получающего экземпляры через наследование классов
}

void TOntology::TestClassInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);

    QFETCH(QSet<QString>, classInstances);

    QCOMPARE(ontology.classInstances(className), classInstances);
}

void TOntology::TestAnyClassInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QStringList> ("classNames");

    QTest::addColumn <QSet<QString> > ("classInstances");

    QTest::newRow("empty-antology") << (Ontology(QSet<Triple>()))
                                    <<(QStringList())
                                   <<(QSet<QString>());

    QTest::newRow("class-without-instances") << (Ontology(QSet<Triple>()
                                                          << Triple("class1", Ontology::IS, Ontology::CLASS)))
                                             <<(QStringList()
                                                <<"class1")
                                            <<(QSet<QString>());

    QTest::newRow("class-with-one-instance") << (Ontology(QSet<Triple>()
                                                          << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                          << Triple("instance1", Ontology::IS, "class1")
                                                          ))
                                             <<(QStringList()
                                                << "class1"
                                                )
                                            <<(QSet<QString>()
                                               << "instance1"
                                               );

    QTest::newRow("fake-class-as-argument") << (Ontology(QSet<Triple>()
                                                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                         << Triple("instance1", Ontology::IS, "class1")))
                                            <<(QStringList()
                                               << "class2")
                                           <<(QSet<QString>());

    QTest::newRow("class-has-instances-as-instances-of-other-class") << (Ontology(QSet<Triple>()
                                                                                  << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                  << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                  << Triple("class1", Ontology::CONTAINS, "class2")
                                                                                  << Triple("instance1", Ontology::IS, "class2")))
                                                                     <<(QStringList()
                                                                        << "class1")
                                                                    <<(QSet<QString>()<<"instance1");

    QTest::newRow("class-has-instances-as-instances-of-other-class-2") << (Ontology(QSet<Triple>()
                                                                                    << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                    << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                    << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                    << Triple("class1", Ontology::CONTAINS, "class2")
                                                                                    << Triple("class2", Ontology::CONTAINS, "class3")
                                                                                    << Triple("instance1", Ontology::IS, "class1")))
                                                                       <<(QStringList()
                                                                          << "class1")
                                                                      <<(QSet<QString>()<<"instance1");

    //запрос к пустой онтологии;класс без экземпляров; класс с одним экземляров; запрос для класса, отсутсвующего в онтологии; запрос для класса, получающего экземпляры через наследование классов
}

void TOntology::TestAnyClassInstances()
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

    QTest::newRow("class-without-instances") << (Ontology(QSet<Triple>()
                                                          << Triple("class1", Ontology::IS, Ontology::CLASS)))
                                             <<(QStringList())
                                            <<(QSet<QString>());

    //    QTest::newRow("class-with-one-instance") << (Ontology(QSet<Triple>()
    //                              << Triple("class1", Ontology::IS, Ontology::CLASS)
    //                              << Triple("instance1", Ontology::IS, "class1")))
    //                              <<(QStringList()
    //                                 <<"class1"
    //                                 <<"class2")
    //                             <<(QSet<QString>());

    //    QTest::newRow("class-with-one-instance") << (Ontology(QSet<Triple>()
    //                              << Triple("class1", Ontology::IS, Ontology::CLASS)
    //                              << Triple("instance1", Ontology::IS, "class1")
    //                                                          ))
    //                              <<(QStringList()
    //                                 <<"class3"
    //                                 <<"class4"
    //                                 )
    //                             <<(QSet<QString>());

    QTest::newRow("class-with-2-instances-and-inheritance") << (Ontology(QSet<Triple>()
                                                                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class5", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class6", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class7", Ontology::IS, Ontology::CLASS)
                                                                         << Triple("class1", Ontology::CONTAINS, "class2")
                                                                         << Triple("class2", Ontology::CONTAINS, "class4")
                                                                         << Triple("class4", Ontology::CONTAINS, "class6")
                                                                         << Triple("class1", Ontology::CONTAINS, "class3")
                                                                         << Triple("class3", Ontology::CONTAINS, "class5")
                                                                         << Triple("class5", Ontology::CONTAINS, "class7")
                                                                         << Triple("instance1", Ontology::IS, "class6")
                                                                         << Triple("instance2", Ontology::IS, "class7")))
                                                            <<(QStringList()
                                                               <<"class2"
                                                               <<"class3")
                                                           <<(QSet<QString>());

    //запрос к пустой онтологии;класс без экземпляров; класс с одним экземляров; запрос для класса, отсутсвующего в онтологии; запрос для класса, получающего экземпляры через наследование классов
}

void TOntology::TestAllClassInstances()
{
    QFETCH(Ontology, ontology);
    QFETCH(QStringList, classNames);

    QFETCH(QSet<QString>, classInstances);

    QCOMPARE(ontology.allClassInstances(classNames), classInstances);
}

void TOntology::TestAllClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");

    QTest::addColumn <QSet<QString> > ("allClasses");

    QTest::newRow("Empty-ontology") << (Ontology(QSet<Triple>()
                                                 ))
                                    <<(QSet<QString>()
                                       );

    QTest::newRow("ontology-with-1-class") << (Ontology(QSet<Triple>()
                                                        <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                        ))
                                           <<(QSet<QString>()
                                              <<"class1"
                                              );

    QTest::newRow("ontology-with-inheritance") << (Ontology(QSet<Triple>()
                                                            <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                            <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                            <<Triple("class1", Ontology::CONTAINS, "class2")
                                                            ))
                                               <<(QSet<QString>()
                                                  <<"class1"
                                                  <<"class2");

    //тест для пустой онтологии; для онтологии без классов; для онтологии с одним классом; для онтологии с наследуемыми классами
}

void TOntology::TestAllClasses()
{
    QFETCH(Ontology, ontology);

    QFETCH(QSet<QString>, allClasses);

    QCOMPARE(ontology.allClasses(), allClasses);
}

void TOntology::TestAllInstances_data()
{
    QTest::addColumn <Ontology> ("ontology");

    QTest::addColumn <QSet<QString> > ("allInstances");

    QTest::newRow("Empty-ontology") << (Ontology(QSet<Triple>()
                                                 ))
                                    <<(QSet<QString>()
                                       );

    QTest::newRow("Ontology-without-classes") << (Ontology(QSet<Triple>()
                                                           <<Triple("cat", Ontology::IS,"animal")
                                                           <<Triple("dog", Ontology::IS,"animal")
                                                           ))
                                              <<(QSet<QString>()
                                                 );


    QTest::newRow("Ontology-with-1-class") << (Ontology(QSet<Triple>()
                                                        <<Triple("cat", Ontology::IS,"animal")
                                                        <<Triple("dog", Ontology::IS,"animal")
                                                        <<Triple("animal", Ontology::IS, Ontology::CLASS)
                                                        ))
                                           <<(QSet<QString>()
                                              <<"cat"
                                              <<"dog"
                                              );

    QTest::newRow("Ontology-with-2-classes") << (Ontology(QSet<Triple>()
                                                          <<Triple("cat", Ontology::IS,"animal")
                                                          <<Triple("dog", Ontology::IS,"another_animal")
                                                          <<Triple("animal", Ontology::IS, Ontology::CLASS)
                                                          <<Triple("another_animal", Ontology::IS, Ontology::CLASS)
                                                          ))
                                             <<(QSet<QString>()
                                                <<"cat"
                                                <<"dog"
                                                );

    QTest::newRow("Ontology-with-2-classes-without-instances") << (Ontology(QSet<Triple>()
                                                                            <<Triple("animal", Ontology::IS, Ontology::CLASS)
                                                                            <<Triple("another_animal", Ontology::IS, Ontology::CLASS)
                                                                            ))
                                                               <<(QSet<QString>()
                                                                  );

    QTest::newRow("Ontology-with-inheritance-class") << (Ontology(QSet<Triple>()
                                                                  <<Triple("cat", Ontology::IS,"animal")
                                                                  <<Triple("dog", Ontology::IS,"another_animal")
                                                                  <<Triple("animal", Ontology::IS, Ontology::CLASS)
                                                                  <<Triple("another_animal", Ontology::IS, Ontology::CLASS)
                                                                  <<Triple("animal", Ontology::CONTAINS, "another_animal")
                                                                  ))
                                                     <<(QSet<QString>()
                                                        <<"cat"
                                                        <<"dog"
                                                        );
    //тест для пустой онтологии; для онтологии без классов; для онтологии с одним классом; для онтологии с двумя классами;для класса без экземпляров;для онтологии с наследуемыми классами
}

void TOntology::TestAllInstances()
{
    QFETCH(Ontology, ontology);

    QFETCH(QSet<QString>, allInstances);

    QCOMPARE(ontology.allInstances(), allInstances);
}

void TOntology::TestClassesForInstance_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("instanceName");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("empty-ontology") << (Ontology(QSet<Triple>()
                                                 ))
                                    <<"instance1"
                                   <<(QSet<QString>()
                                      );

    QTest::newRow("one-class") << (Ontology(QSet<Triple>()
                                            <<(Triple("class1", Ontology::IS, Ontology::CLASS))
                                            <<(Triple("instance1", Ontology::IS, "class1"))))
                               <<"instance1"
                              <<(QSet<QString>()
                                 <<"class1");

    QTest::newRow("two-classes-with-inheritance") << (Ontology(QSet<Triple>()
                                                               <<(Triple("class1", Ontology::IS, Ontology::CLASS))
                                                               <<(Triple("class2", Ontology::IS, Ontology::CLASS))
                                                               <<(Triple("class1", Ontology::CONTAINS, "class2"))
                                                               <<(Triple("instance1", Ontology::IS, "class2"))
                                                               ))
                                                  <<"instance1"
                                                 <<(QSet<QString>()
                                                    <<"class1"
                                                    <<"class2"
                                                    );

    //    QTest::newRow("incorrect-ontology-without-class-decloration") << (Ontology(QSet<Triple>()
    //                                            <<(Triple("class1", Ontology::CONTAINS, "class2"))
    //                                            <<(Triple("instance1", Ontology::IS, "class1"))
    //                                           ))
    //                              <<"instance1"
    //                             <<(QSet<QString>()
    //                                );

    //тесты для пустой онтологии;для одного класса;для двух, трёх классов с наследованием;для некорректно онтологии без объявления классов
}

void TOntology::TestClassesForInstance()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, instanceName);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.classesForInstance(instanceName), classes);
}

void TOntology::TestSubClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("subClasses");

    QTest::newRow("empty-ontology") << (Ontology(QSet<Triple>()))
                                    <<"class1"
                                   <<(QSet<QString>());

    QTest::newRow("ontology-without-classes") << (Ontology(QSet<Triple>()
                                                           <<Triple("class1",Ontology::CONTAINS,"class2")
                                                           <<Triple("class2",Ontology::CONTAINS,"class3")
                                                           <<Triple("instance1",Ontology::IS,"class1")
                                                           <<Triple("instance2",Ontology::IS,"class2")))
                                              <<"class2"
                                             <<(QSet<QString>());

    QTest::newRow("ontology-with-1-class") << (Ontology(QSet<Triple>()
                                                        <<Triple("instance1",Ontology::IS,"class1")
                                                        <<Triple("instance2",Ontology::IS,"class2")
                                                        <<Triple("class1",Ontology::IS,Ontology::CLASS)))
                                           <<"class1"
                                          <<(QSet<QString>());

    QTest::newRow("ontology-with-2-classes") << (Ontology(QSet<Triple>()
                                                          <<Triple("instance1",Ontology::IS,"class1")
                                                          <<Triple("instance2",Ontology::IS,"class2")
                                                          <<Triple("class1",Ontology::IS,Ontology::CLASS)
                                                          <<Triple("class2",Ontology::IS,Ontology::CLASS)))
                                             <<"class1"
                                            <<(QSet<QString>());

    QTest::newRow("ontology-with-3-classes-and-inheritance") << (Ontology(QSet<Triple>()
                                                                          <<Triple("class1",Ontology::CONTAINS,"class2")
                                                                          <<Triple("class2",Ontology::CONTAINS,"class3")
                                                                          <<Triple("instance1",Ontology::IS,"class1")
                                                                          <<Triple("instance2",Ontology::IS,"class2")
                                                                          <<Triple("class1",Ontology::IS,Ontology::CLASS)
                                                                          <<Triple("class2",Ontology::IS,Ontology::CLASS)
                                                                          <<Triple("class3",Ontology::IS,Ontology::CLASS)))
                                                             <<"class1"
                                                            <<(QSet<QString>()
                                                               <<"class2"
                                                               <<"class3");

    //тест для пустой онтологии; для онтологии без классов; для онтологии с одним классом; для онтологии с двумя классами;для онтологии с наследуемыми классами
}

void TOntology::TestSubClasses()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);

    QFETCH(QSet<QString>, subClasses);

    QCOMPARE(ontology.subClasses(className), subClasses);
}

void TOntology::TestSuperClasses_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");

    QTest::addColumn <QSet<QString> > ("superClasses");

    QTest::newRow("empty-ontology") << (Ontology(QSet<Triple>()
                                                 ))
                                    <<""
                                   <<(QSet<QString>()
                                      );

    QTest::newRow("ontology-without-classes") << (Ontology(QSet<Triple>()
                                                           << Triple("instance1", Ontology::IS, "class1")
                                                           ))
                                              <<""
                                             <<(QSet<QString>()
                                                );

    //тест для пустой онтологии; для онтологии без классов; для онтологии с одним классом; для онтологии с двумя классами;для онтологии с наследуемыми классами
}

void TOntology::TestSuperClasses()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);

    QFETCH(QSet<QString>, superClasses);

    QCOMPARE(ontology.superClasses(className), superClasses);
}

void TOntology::TestMainSuperClass_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("instance1");
    QTest::addColumn <QString> ("instance2");

    QTest::addColumn <QSet<QString> > ("classes");

    QTest::newRow("empty-ontology") << (Ontology(QSet<Triple>()))
                                    <<("1")
                                   <<("2")
                                  <<(QSet<QString>()
                                     );

    QTest::newRow("ontology-without-class-decraration") << (Ontology(QSet<Triple>()
                                                                     <<Triple("instance1", Ontology::IS, "class1")
                                                                     <<Triple("instance2", Ontology::IS, "class1")
                                                                     <<Triple("instance3", Ontology::IS, "class1")
                                                                     ))
                                                        <<("1")
                                                       <<("2")
                                                      <<(QSet<QString>()
                                                         );

    QTest::newRow("1 minimal class") << (Ontology(QSet<Triple>()
                                                  <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class3", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class4", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class1", Ontology::CONTAINS, "class2")
                                                  <<Triple("class2", Ontology::CONTAINS, "class3")
                                                  <<Triple("class3", Ontology::CONTAINS, "class4")
                                                  <<Triple("instance1", Ontology::IS, "class3")
                                                  <<Triple("instance2", Ontology::IS, "class3")
                                                  <<Triple("instance1", Ontology::IS, "class4")
                                                  <<Triple("instance2", Ontology::IS, "class4")))
                                     <<("instance1")
                                    <<("instance2")
                                   <<(QSet<QString>()
                                      <<"class3");

    QTest::newRow("2 minimal class") << (Ontology(QSet<Triple>()
                                                  <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class3", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class4", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class1", Ontology::CONTAINS, "class2")
                                                  <<Triple("class2", Ontology::CONTAINS, "class3")
                                                  <<Triple("class2", Ontology::CONTAINS, "class4")
                                                  <<Triple("instance1", Ontology::IS, "class3")
                                                  <<Triple("instance2", Ontology::IS, "class3")
                                                  <<Triple("instance1", Ontology::IS, "class4")
                                                  <<Triple("instance2", Ontology::IS, "class4")))
                                     <<("instance1")
                                    <<("instance2")
                                   <<(QSet<QString>()
                                      <<"class3"
                                      <<"class4");

    QTest::newRow("3 minimal class") << (Ontology(QSet<Triple>()
                                                  <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class3", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class4", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class5", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class1", Ontology::CONTAINS, "class2")
                                                  <<Triple("class2", Ontology::CONTAINS, "class3")
                                                  <<Triple("class2", Ontology::CONTAINS, "class4")
                                                  <<Triple("class2", Ontology::CONTAINS, "class5")
                                                  <<Triple("instance1", Ontology::IS, "class3")
                                                  <<Triple("instance2", Ontology::IS, "class3")
                                                  <<Triple("instance1", Ontology::IS, "class4")
                                                  <<Triple("instance2", Ontology::IS, "class4")
                                                  <<Triple("instance1", Ontology::IS, "class5")
                                                  <<Triple("instance2", Ontology::IS, "class5")))
                                     <<("instance1")
                                    <<("instance2")
                                   <<(QSet<QString>()
                                      <<"class3"
                                      <<"class4"
                                      <<"class5");

    QTest::newRow("0 minimal class") << (Ontology(QSet<Triple>()
                                                  <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class3", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class4", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class5", Ontology::IS, Ontology::CLASS)
                                                  <<Triple("class1", Ontology::CONTAINS, "class2")
                                                  <<Triple("class2", Ontology::CONTAINS, "class3")
                                                  <<Triple("class2", Ontology::CONTAINS, "class4")
                                                  <<Triple("class2", Ontology::CONTAINS, "class5")
                                                  <<Triple("instance1", Ontology::IS, "class1")
                                                  <<Triple("instance2", Ontology::IS, "class2")
                                                  <<Triple("instance1", Ontology::IS, "class3")
                                                  <<Triple("instance2", Ontology::IS, "class4")
                                                  <<Triple("instance1", Ontology::IS, "class5")))
                                     <<("instance1")
                                    <<("instance2")
                                   <<(QSet<QString>());

    //для пустой онтотологии; для онтологии без объявления классов; для одного, двух, трёх, минимальных классов; для отсутвующего минимального класса
}

void TOntology::TestMainSuperClass()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, instance1);
    QFETCH(QString, instance2);

    QFETCH(QSet<QString>, classes);

    QCOMPARE(ontology.mainSuperClass(instance1, instance2), classes);
}


void TOntology::TestIsValid_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <bool> ("isItValid");

    QTest::newRow("TestNum1") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology::CONTAINS,"b")
                                           << Triple("b", Ontology::CONTAINS,"a")
                                           << Triple("a", Ontology::IS, Ontology::CLASS)
                                           << Triple("b", Ontology::IS, Ontology::CLASS)))
                              <<false;

    QTest::newRow("TestNum2") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology::CONTAINS,"b")
                                           << Triple("a", Ontology::CONTAINS,"c")
                                           << Triple("c", Ontology::CONTAINS,"d")
                                           << Triple("d", Ontology::CONTAINS,"c")
                                           << Triple("a", Ontology::IS, Ontology::CLASS)
                                           << Triple("b", Ontology::IS, Ontology::CLASS)
                                           << Triple("c", Ontology::IS, Ontology::CLASS)
                                           << Triple("d", Ontology::IS, Ontology::CLASS)))
                              <<false;

    QTest::newRow("TestNum3") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology::CONTAINS,"b")
                                           << Triple("a", Ontology::CONTAINS,"d")
                                           << Triple("b", Ontology::CONTAINS,"c")
                                           << Triple("d", Ontology::CONTAINS,"f")
                                           << Triple("d", Ontology::CONTAINS,"e")
                                           << Triple("a", Ontology::IS, Ontology::CLASS)
                                           << Triple("b", Ontology::IS, Ontology::CLASS)
                                           << Triple("c", Ontology::IS, Ontology::CLASS)
                                           << Triple("d", Ontology::IS, Ontology::CLASS)
                                           << Triple("e", Ontology::IS, Ontology::CLASS)
                                           << Triple("f", Ontology::IS, Ontology::CLASS)))
                              <<true;

    QTest::newRow("TestNum4") << (Ontology(QSet<Triple>()
                                           << Triple("a", Ontology::CONTAINS,"b")
                                           << Triple("b", Ontology::CONTAINS,"c")
                                           << Triple("c", Ontology::CONTAINS,"d")
                                           << Triple("d", Ontology::CONTAINS,"a")
                                           << Triple("a", Ontology::IS, Ontology::CLASS)
                                           << Triple("b", Ontology::IS, Ontology::CLASS)
                                           << Triple("c", Ontology::IS, Ontology::CLASS)
                                           << Triple("d", Ontology::IS, Ontology::CLASS)
                                           ))
                              <<false;

    //тесты со сложной иерархией классов типа A > B, B > C, C > A

}

void TOntology::TestIsValid()
{
    QFETCH(Ontology, ontology);
    QFETCH(bool, isItValid);

    QCOMPARE(ontology.isValid(), isItValid);
}

void TOntology::TestIsMinimal_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <bool> ("isItMinimal");

    QTest::newRow("4 classes, 1 header class, 1 instance (1 class), minimal true") << (Ontology(QSet<Triple>()
                                                                                                << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                << Triple("instance1", Ontology::IS, "class4")
                                                                                                ))
                                                                                   <<true;

    QTest::newRow("4 classes, 1 header class, 1 instance (2 classes), minimal true") << (Ontology(QSet<Triple>()
                                                                                                  << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                  << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                  << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                  << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                  << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                  << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                  << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                  << Triple("instance1", Ontology::IS, "class4")
                                                                                                  << Triple("instance1", Ontology::IS, "class3")
                                                                                                  ))
                                                                                     <<true;

    QTest::newRow("4 classes, 1 header class, 2 instances (1 class each), minimal true") << (Ontology(QSet<Triple>()
                                                                                                      << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                      << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                      << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                      << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                      << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                      << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                      << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                      << Triple("instance1", Ontology::IS, "class4")
                                                                                                      << Triple("instance2", Ontology::IS, "class3")
                                                                                                      ))
                                                                                         <<true;

    QTest::newRow("4 classes, 1 header class, 1 instances (2 classes), minimal false") << (Ontology(QSet<Triple>()
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                    << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                    << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("instance1", Ontology::IS, "class4")
                                                                                                    << Triple("instance1", Ontology::IS, "class2")))
                                                                                       <<false;

    QTest::newRow("4 classes, 1 header class, 2 instances (2 classes), minimal false") << (Ontology(QSet<Triple>()
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                    << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                    << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("instance1", Ontology::IS, "class4")
                                                                                                    << Triple("instance1", Ontology::IS, "class2")
                                                                                                    << Triple("instance2", Ontology::IS, "class4")
                                                                                                    << Triple("instance2", Ontology::IS, "class1")))
                                                                                       <<false;
}

void TOntology::TestIsMinimal()
{
    QFETCH(Ontology, ontology);
    QFETCH(bool, isItMinimal);

    QCOMPARE(ontology.isMinimal(),isItMinimal);
}


void TOntology::TestMinimalize_data()
{
    QTest::addColumn <Ontology> ("ontology1");
    QTest::addColumn <bool> ("isminimal");

    QTest::newRow("3 classes, 1 instance (3 classes), minimal false") << (Ontology(QSet<Triple>()
                                                                                   <<Triple("instance1", Ontology::IS, "class1")
                                                                                   <<Triple("instance1", Ontology::IS, "class2")
                                                                                   <<Triple("instance1", Ontology::IS, "class3")
                                                                                   <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                   <<Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                   <<Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                   <<Triple("class1", Ontology::CONTAINS, "class2")
                                                                                   <<Triple("class2", Ontology::CONTAINS, "class3")
                                                                                   <<Triple("instance1", Ontology::IS, "class1")
                                                                                   <<Triple("instance1", Ontology::IS, "class2")
                                                                                   <<Triple("instance1", Ontology::IS, "class3")))
                                                                      <<true;

    QTest::newRow("4 classes, 1 header class, 2 instances (2 classes), minimal false") << (Ontology(QSet<Triple>()
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                    << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                    << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("instance1", Ontology::IS, "class4")
                                                                                                    << Triple("instance1", Ontology::IS, "class2")
                                                                                                    << Triple("instance2", Ontology::IS, "class4")
                                                                                                    << Triple("instance2", Ontology::IS, "class1")))
                                                                                       <<true;

    QTest::newRow("4 classes, 1 header class, 1 instances (2 classes), minimal false") << (Ontology(QSet<Triple>()
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class2")
                                                                                                    << Triple("class1", Ontology::CONTAINS,"class3")
                                                                                                    << Triple("class2", Ontology::CONTAINS,"class4")
                                                                                                    << Triple("class1", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class2", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class3", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("class4", Ontology::IS, Ontology::CLASS)
                                                                                                    << Triple("instance1", Ontology::IS, "class4")
                                                                                                    << Triple("instance1", Ontology::IS, "class2")))
                                                                                       <<true;
}

void TOntology::TestMinimalize()
{
    QFETCH(Ontology, ontology1);
    QFETCH(bool, isminimal);

    if(!ontology1.isMinimal())
    {
        ontology1.minimalize();
    }

    QCOMPARE(ontology1.isMinimal(), true);
}

void TOntology::TestClassProperties_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("className");
    QTest::addColumn <QSet<QString> > ("properties");

    QTest::newRow("inheritance, 7 classes, 2 header classes, 7 properties, 1 instance")
            <<Ontology(QSet<Triple>()
                       <<Triple("classA", Ontology::IS, Ontology::CLASS)
                       <<Triple("classB", Ontology::IS, Ontology::CLASS)
                       <<Triple("classC", Ontology::IS, Ontology::CLASS)
                       <<Triple("classD", Ontology::IS, Ontology::CLASS)
                       <<Triple("class1", Ontology::IS, Ontology::CLASS)
                       <<Triple("class2", Ontology::IS, Ontology::CLASS)
                       <<Triple("class3", Ontology::IS, Ontology::CLASS)
                       <<Triple("classG", Ontology::IS, Ontology::CLASS)
                       <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                       <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                       <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                       <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                       <<Triple("class1", Ontology::HAS_PROPERTY, "property5")
                       <<Triple("class2", Ontology::HAS_PROPERTY, "property6")
                       <<Triple("class3", Ontology::HAS_PROPERTY, "property7")
                       <<Triple("classD", Ontology::CONTAINS, "classC")
                       <<Triple("classC", Ontology::CONTAINS, "classB")
                       <<Triple("classB", Ontology::CONTAINS, "classA")
                       <<Triple("class3", Ontology::CONTAINS, "class2")
                       <<Triple("class2", Ontology::CONTAINS, "class1")
                       <<Triple("class1", Ontology::CONTAINS, "classG")
                       <<Triple("classA", Ontology::CONTAINS, "classG")
                       <<Triple("instance1", Ontology::IS, "class1")
                       <<Triple("instance1", Ontology::IS, "classA"))
           <<QString("classG")
          <<(QSet<QString>()
             <<"property1"
             <<"property2"
             <<"property3"
             <<"property4"
             <<"property5"
             <<"property6"
             <<"property7");

    QTest::newRow("inheritance, 7 classes, 2 header classes, 7 properties, 1 instance")
            <<Ontology(QSet<Triple>()
                       <<Triple("classA", Ontology::IS, Ontology::CLASS)
                       <<Triple("classB", Ontology::IS, Ontology::CLASS)
                       <<Triple("classC", Ontology::IS, Ontology::CLASS)
                       <<Triple("classD", Ontology::IS, Ontology::CLASS)
                       <<Triple("class1", Ontology::IS, Ontology::CLASS)
                       <<Triple("class2", Ontology::IS, Ontology::CLASS)
                       <<Triple("class3", Ontology::IS, Ontology::CLASS)
                       <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                       <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                       <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                       <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                       <<Triple("class1", Ontology::HAS_PROPERTY, "property5")
                       <<Triple("class2", Ontology::HAS_PROPERTY, "property6")
                       <<Triple("class3", Ontology::HAS_PROPERTY, "property7")
                       <<Triple("classD", Ontology::CONTAINS, "classC")
                       <<Triple("classC", Ontology::CONTAINS, "classB")
                       <<Triple("classB", Ontology::CONTAINS, "classA")
                       <<Triple("class3", Ontology::CONTAINS, "class2")
                       <<Triple("class2", Ontology::CONTAINS, "class1")
                       <<Triple("instance1", Ontology::IS, "class1")
                       <<Triple("instance1", Ontology::IS, "classA"))
           <<QString("classA")
          <<(QSet<QString>()
             <<"property1"
             <<"property2"
             <<"property3"
             <<"property4");

    QTest::newRow("inheritance, 4 classes, 1 header class, 4 properties, 1 instance")
            <<Ontology(QSet<Triple>()
                       <<Triple("classA", Ontology::IS, Ontology::CLASS)
                       <<Triple("classB", Ontology::IS, Ontology::CLASS)
                       <<Triple("classC", Ontology::IS, Ontology::CLASS)
                       <<Triple("classD", Ontology::IS, Ontology::CLASS)
                       <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                       <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                       <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                       <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                       <<Triple("classD", Ontology::CONTAINS, "classC")
                       <<Triple("classC", Ontology::CONTAINS, "classB")
                       <<Triple("classB", Ontology::CONTAINS, "classA")
                       <<Triple("instance1", Ontology::IS, "classA"))
           <<QString("classA")
          <<(QSet<QString>()
             <<"property1"
             <<"property2"
             <<"property3"
             <<"property4");

    QTest::newRow("no inheritance, 1 class, 1 header class, 1 propertie, 1 instance")
            <<Ontology(QSet<Triple>()
                       <<Triple("classA", Ontology::IS, Ontology::CLASS)
                       <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                       <<Triple("instance1", Ontology::IS, "classA"))
           <<QString("classA")
          <<(QSet<QString>()
             <<"property1");

    QTest::newRow("no inheritance, 1 class, 1 header class, 1 propertie, 1 instance, wrong class name")
            <<Ontology(QSet<Triple>()
                       <<Triple("classA", Ontology::IS, Ontology::CLASS)
                       <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                       <<Triple("instance1", Ontology::IS, "classA"))
           <<QString("classB")
          <<QSet<QString>();

    QTest::newRow("no inheritance, no classes, 0 propertie, 0 instances, no class name")
            <<Ontology(QSet<Triple>())
           <<QString()
          <<QSet<QString>();

}

void TOntology::TestClassProperties()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, className);
    QFETCH(QSet<QString>, properties);

    QCOMPARE(ontology.classProperties(className), properties);
}

void TOntology::TestPropertyValues_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("propertyName");
    QTest::addColumn <QSet<QString> > ("propertyvalues");

    QTest::newRow("3 classes, without branching, 1 header classes, 1 instance")<<(Ontology(QSet<Triple>()
                                                                                           <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                           <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                           <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                           <<Triple("instance1", Ontology::IS, "classC")
                                                                                           <<Triple("instance1", "property1", "value1")
                                                                                           <<Triple("instance1", "property1", "value2")
                                                                                           <<Triple("instance1", "property1", "value3")))
                                                                              <<QString("property1")
                                                                             <<(QSet<QString>()
                                                                                <<"value1"
                                                                                <<"value2"
                                                                                <<"value3");

    QTest::newRow("4 classes, with branching, 1 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("instance1", Ontology::IS, "classC")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property1", "value2")
                                                                                         <<Triple("instance1", "property1", "value3")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                         <<Triple("instance2", "property1", "value5")
                                                                                         <<Triple("instance2", "property1", "value6")))
                                                                            <<QString("property1")
                                                                           <<(QSet<QString>()
                                                                              <<"value1"
                                                                              <<"value2"
                                                                              <<"value3"
                                                                              <<"value4"
                                                                              <<"value5"
                                                                              <<"value6");

    QTest::newRow("6 classes, with branching, 2 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classC", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("instance1", Ontology::IS, "classB")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property1", "value2")
                                                                                         <<Triple("instance1", "property1", "value3")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                         <<Triple("instance2", "property1", "value5")
                                                                                         <<Triple("instance2", "property1", "value6")))
                                                                            <<QString("property1")
                                                                           <<(QSet<QString>()
                                                                              <<"value1"
                                                                              <<"value2"
                                                                              <<"value3"
                                                                              <<"value4"
                                                                              <<"value5"
                                                                              <<"value6");

    QTest::newRow("6 classes, with branching, 2 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classE", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classE")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classF")
                                                                                         <<Triple("classC", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classD", Ontology::CONTAINS, "classG")
                                                                                         <<Triple("classD", Ontology::CONTAINS, "classK")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("instance1", Ontology::IS, "classE")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property1", "value2")
                                                                                         <<Triple("instance1", "property1", "value3")
                                                                                         <<Triple("instance2", Ontology::IS, "classG")
                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                         <<Triple("instance2", "property1", "value5")
                                                                                         <<Triple("instance2", "property1", "value6")))
                                                                            <<QString("property1")
                                                                           <<(QSet<QString>()
                                                                              <<"value1"
                                                                              <<"value2"
                                                                              <<"value3"
                                                                              <<"value4"
                                                                              <<"value5"
                                                                              <<"value6");

    QTest::newRow("6 classes, with branching, 2 header classes, 2 instances, fake property")<<(Ontology(QSet<Triple>()
                                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classE", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                                         <<Triple("classB", Ontology::CONTAINS, "classE")
                                                                                                         <<Triple("classB", Ontology::CONTAINS, "classF")
                                                                                                         <<Triple("classC", Ontology::CONTAINS, "classD")
                                                                                                         <<Triple("classD", Ontology::CONTAINS, "classG")
                                                                                                         <<Triple("classD", Ontology::CONTAINS, "classK")
                                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property1")
                                                                                                         <<Triple("instance1", Ontology::IS, "classE")
                                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                                         <<Triple("instance1", "property1", "value2")
                                                                                                         <<Triple("instance1", "property1", "value3")
                                                                                                         <<Triple("instance2", Ontology::IS, "classG")
                                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                                         <<Triple("instance2", "property1", "value5")
                                                                                                         <<Triple("instance2", "property1", "value6")))
                                                                                            <<QString("property2")
                                                                                           <<(QSet<QString>());
}

void TOntology::TestPropertyValues()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, propertyName);
    QFETCH(QSet<QString>, propertyvalues);

    QCOMPARE(ontology.propertyValues(propertyName),propertyvalues);
}

void TOntology::TestInstanceProperties_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <QString> ("instanceName");
    QTest::addColumn <MyHash> ("instanceproperties");

    QTest::newRow("3 classes, without branching, 1 header classes, 1 instance")<<(Ontology(QSet<Triple>()
                                                                                           <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                           <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                           <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                           <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                           <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                           <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                           <<Triple("instance1", Ontology::IS, "classC")
                                                                                           <<Triple("instance1", "property1", "value1")))
                                                                              <<QString("instance1")
                                                                             <<(MyHash()
                                                                                .insertInc("property3",QString())
                                                                                .insertInc("property2",QString())
                                                                                .insertInc("property1","value1"));

    QTest::newRow("3 classes, without branching, 1 header classes, 1 instance, with fake instance")<<(Ontology(QSet<Triple>()
                                                                                                               <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                                               <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                                               <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                                               <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                                               <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                                               <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                                               <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                                               <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                                               <<Triple("instance1", Ontology::IS, "classC")
                                                                                                               <<Triple("instance1", "property1", "value1")))
                                                                                                  <<QString("instance15")
                                                                                                 <<(MyHash());

    QTest::newRow("4 classes, with branching, 1 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                         <<Triple("instance1", Ontology::IS, "classC")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property2", "value2")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value3")
                                                                                         <<Triple("instance2", "property2", "value4")))
                                                                            <<QString("instance1")
                                                                           <<(MyHash()
                                                                              .insertInc("property3",QString())
                                                                              .insertInc("property2","value2")
                                                                              .insertInc("property1","value1"));

    QTest::newRow("4 classes, with branching, 1 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                         <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                         <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                                         <<Triple("instance1", Ontology::IS, "classC")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property2", "value2")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value3")
                                                                                         <<Triple("instance2", "property2", "value4")))
                                                                            <<QString("instance2")
                                                                           <<(MyHash()
                                                                              .insertInc("property4",QString())
                                                                              .insertInc("property2","value4")
                                                                              .insertInc("property1","value3"));

    QTest::newRow("6 classes, with branching, 2 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classC", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                         <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                                         <<Triple("instance1", Ontology::IS, "classB")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property2", "value2")
                                                                                         <<Triple("instance1", "property3", "value3")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                         <<Triple("instance2", "property2", "value5")
                                                                                         <<Triple("instance2", "property3", "value6")))
                                                                            <<QString("instance1")
                                                                           <<(MyHash()
                                                                              .insertInc("property1", "value1")
                                                                              .insertInc("property2", "value2"));

    QTest::newRow("6 classes, with branching, 2 header classes, 2 instances")<<(Ontology(QSet<Triple>()
                                                                                         <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                         <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                         <<Triple("classC", Ontology::CONTAINS, "classD")
                                                                                         <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                         <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                         <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                         <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                                         <<Triple("instance1", Ontology::IS, "classB")
                                                                                         <<Triple("instance1", "property1", "value1")
                                                                                         <<Triple("instance1", "property2", "value2")
                                                                                         <<Triple("instance1", "property3", "value3")
                                                                                         <<Triple("instance2", Ontology::IS, "classD")
                                                                                         <<Triple("instance2", "property1", "value4")
                                                                                         <<Triple("instance2", "property2", "value5")
                                                                                         <<Triple("instance2", "property3", "value6")))
                                                                            <<QString("instance2")
                                                                           <<(MyHash()
                                                                              .insertInc("property3", "value6")
                                                                              .insertInc("property4", QString()));

    QTest::newRow("empty-ontology")<<(Ontology(QSet<Triple>()))
                                  <<QString("instance1")
                                 <<(MyHash());

    QTest::newRow("empty-ontology, no instance")<<(Ontology(QSet<Triple>()))
                                               <<QString()
                                              <<(MyHash());
}

void TOntology::TestInstanceProperties()
{
    QFETCH(Ontology, ontology);
    QFETCH(QString, instanceName);
    QFETCH(MyHash, instanceproperties);

    QCOMPARE(ontology.instanceProperties(instanceName),instanceproperties);
}

void TOntology::TestInstancesForProperties_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <MyHash> ("values");
    QTest::addColumn <QSet<QString> > ("instances");

    QTest::newRow("empty ontology, empty values")<<(Ontology(QSet<Triple>()))
                                                <<(MyHash())
                                               <<(QSet<QString>());

    QTest::newRow("3 classes, no branching, 1 header class")<<(Ontology(QSet<Triple>()
                                                                        <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                        <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                        <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                        <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                        <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                        <<Triple("instance1", Ontology::IS, "classC")
                                                                        <<Triple("instance2", Ontology::IS, "classC")
                                                                        <<Triple("instance3", Ontology::IS, "classC")
                                                                        <<Triple("instance1", "property1", "value1")
                                                                        <<Triple("instance2", "property2", "value2")
                                                                        <<Triple("instance3", "property3", "value3")))
                                                           <<(MyHash()
                                                              .insertInc("property1", "value1")
                                                              .insertInc("property2", "value2")
                                                              .insertInc("property3", "value3"))
                                                          <<(QSet<QString>()
                                                             <<"instance1"
                                                             <<"instance2"
                                                             <<"instance3");

    QTest::newRow("4 classes, branching, 1 header class")<<(Ontology(QSet<Triple>()
                                                                     <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                     <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                     <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                     <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                     <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                     <<Triple("instance1", Ontology::IS, "classC")
                                                                     <<Triple("instance2", Ontology::IS, "classC")
                                                                     <<Triple("instance3", Ontology::IS, "classD")
                                                                     <<Triple("instance4", Ontology::IS, "classD")
                                                                     <<Triple("instance1", "property1", "value1")
                                                                     <<Triple("instance2", "property2", "value2")
                                                                     <<Triple("instance3", "property1", "value3")
                                                                     <<Triple("instance4", "property2", "value4")))
                                                        <<(MyHash()
                                                           .insertIncMulti("property1", "value1")
                                                           .insertIncMulti("property2", "value2")
                                                           .insertIncMulti("property1", "value3")
                                                           .insertIncMulti("property2", "value4"))
                                                       <<(QSet<QString>()
                                                          <<"instance1"
                                                          <<"instance2"
                                                          <<"instance3"
                                                          <<"instance4");

    QTest::newRow("8 classes, branching, 2 header class")<<(Ontology(QSet<Triple>()
                                                                     <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classL", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                     <<Triple("classF", Ontology::CONTAINS, "classG")
                                                                     <<Triple("classG", Ontology::CONTAINS, "classK")
                                                                     <<Triple("classG", Ontology::CONTAINS, "classL")
                                                                     <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                     <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                     <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                     <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                     <<Triple("classF", Ontology::HAS_PROPERTY, "property5")
                                                                     <<Triple("classG", Ontology::HAS_PROPERTY, "property6")
                                                                     <<Triple("classK", Ontology::HAS_PROPERTY, "property7")
                                                                     <<Triple("classL", Ontology::HAS_PROPERTY, "property8")
                                                                     <<Triple("instance1", Ontology::IS, "classC")
                                                                     <<Triple("instance2", Ontology::IS, "classD")
                                                                     <<Triple("instance3", Ontology::IS, "classK")
                                                                     <<Triple("instance4", Ontology::IS, "classL")
                                                                     <<Triple("instance1", "property1", "value1")
                                                                     <<Triple("instance2", "property2", "value2")
                                                                     <<Triple("instance3", "property5", "value3")
                                                                     <<Triple("instance4", "property6", "value4")))
                                                        <<(MyHash()
                                                           .insertIncMulti("property1", "value1")
                                                           .insertIncMulti("property2", "value2")
                                                           .insertIncMulti("property5", "value3")
                                                           .insertIncMulti("property6", "value4"))
                                                       <<(QSet<QString>()
                                                          <<"instance1"
                                                          <<"instance2"
                                                          <<"instance3"
                                                          <<"instance4");

    QTest::newRow("8 classes, branching, 2 header class fake values")<<(Ontology(QSet<Triple>()
                                                                                 <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classL", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                 <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                 <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                                 <<Triple("classF", Ontology::CONTAINS, "classG")
                                                                                 <<Triple("classG", Ontology::CONTAINS, "classK")
                                                                                 <<Triple("classG", Ontology::CONTAINS, "classL")
                                                                                 <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                 <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                 <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                 <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                                 <<Triple("classF", Ontology::HAS_PROPERTY, "property5")
                                                                                 <<Triple("classG", Ontology::HAS_PROPERTY, "property6")
                                                                                 <<Triple("classK", Ontology::HAS_PROPERTY, "property7")
                                                                                 <<Triple("classL", Ontology::HAS_PROPERTY, "property8")
                                                                                 <<Triple("instance1", Ontology::IS, "classC")
                                                                                 <<Triple("instance2", Ontology::IS, "classD")
                                                                                 <<Triple("instance3", Ontology::IS, "classK")
                                                                                 <<Triple("instance4", Ontology::IS, "classL")
                                                                                 <<Triple("instance1", "property1", "value1")
                                                                                 <<Triple("instance2", "property2", "value2")
                                                                                 <<Triple("instance3", "property5", "value3")
                                                                                 <<Triple("instance4", "property6", "value4")))
                                                                    <<(MyHash()
                                                                       .insertIncMulti("property10", "value1")
                                                                       .insertIncMulti("property12", "value2")
                                                                       .insertIncMulti("property15", "value3")
                                                                       .insertIncMulti("property16", "value4"))
                                                                   <<(QSet<QString>());

}

void TOntology::TestInstancesForProperties()
{
    QFETCH(Ontology, ontology);
    QFETCH(MyHash, values);
    QFETCH(QSet<QString>, instances);

    QCOMPARE(ontology.instancesForProperties(values),instances);
}

void TOntology::TestInstancesForNonProperties_data()
{
    QTest::addColumn <Ontology> ("ontology");
    QTest::addColumn <MyHash> ("values");
    QTest::addColumn <QSet<QString> > ("instances");

    QTest::newRow("empty ontology, empty values")<<(Ontology(QSet<Triple>()))
                                                <<(MyHash())
                                               <<(QSet<QString>());

    QTest::newRow("3 classes, no branching, 1 header class")<<(Ontology(QSet<Triple>()
                                                                        <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                        <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                        <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                        <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                        <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                        <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                        <<Triple("instance1", Ontology::IS, "classC")
                                                                        <<Triple("instance2", Ontology::IS, "classC")
                                                                        <<Triple("instance3", Ontology::IS, "classC")
                                                                        <<Triple("instance1", "property1", "value1")
                                                                        <<Triple("instance2", "property2", "value2")
                                                                        <<Triple("instance3", "property3", "value3")))
                                                           <<(MyHash()
                                                              .insertInc("property1", "value1")
                                                              .insertInc("property2", "value2"))
                                                          <<(QSet<QString>()
                                                             <<"instance3");

    QTest::newRow("4 classes, branching, 1 header class")<<(Ontology(QSet<Triple>()
                                                                     <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                     <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                     <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                     <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                     <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                     <<Triple("instance1", Ontology::IS, "classC")
                                                                     <<Triple("instance2", Ontology::IS, "classC")
                                                                     <<Triple("instance3", Ontology::IS, "classD")
                                                                     <<Triple("instance4", Ontology::IS, "classD")
                                                                     <<Triple("instance1", "property1", "value1")
                                                                     <<Triple("instance2", "property2", "value2")
                                                                     <<Triple("instance3", "property1", "value3")
                                                                     <<Triple("instance4", "property2", "value4")))
                                                        <<(MyHash()
                                                           .insertIncMulti("property1", "value1")
                                                           .insertIncMulti("property2", "value2"))
                                                       <<(QSet<QString>()
                                                          <<"instance3"
                                                          <<"instance4");

    QTest::newRow("8 classes, branching, 2 header class")<<(Ontology(QSet<Triple>()
                                                                     <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classL", Ontology::IS, Ontology::CLASS)
                                                                     <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                     <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                     <<Triple("classF", Ontology::CONTAINS, "classG")
                                                                     <<Triple("classG", Ontology::CONTAINS, "classK")
                                                                     <<Triple("classG", Ontology::CONTAINS, "classL")
                                                                     <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                     <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                     <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                     <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                     <<Triple("classF", Ontology::HAS_PROPERTY, "property5")
                                                                     <<Triple("classG", Ontology::HAS_PROPERTY, "property6")
                                                                     <<Triple("classK", Ontology::HAS_PROPERTY, "property7")
                                                                     <<Triple("classL", Ontology::HAS_PROPERTY, "property8")
                                                                     <<Triple("instance1", Ontology::IS, "classC")
                                                                     <<Triple("instance2", Ontology::IS, "classD")
                                                                     <<Triple("instance3", Ontology::IS, "classK")
                                                                     <<Triple("instance4", Ontology::IS, "classL")
                                                                     <<Triple("instance1", "property1", "value1")
                                                                     <<Triple("instance2", "property2", "value2")
                                                                     <<Triple("instance3", "property5", "value3")
                                                                     <<Triple("instance4", "property6", "value4")))
                                                        <<(MyHash()
                                                           .insertIncMulti("property1", "value1")
                                                           .insertIncMulti("property2", "value2"))
                                                       <<(QSet<QString>()
                                                          <<"instance3"
                                                          <<"instance4");

    QTest::newRow("8 classes, branching, 2 header class fake values")<<(Ontology(QSet<Triple>()
                                                                                 <<Triple("classA", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classB", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classC", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classD", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classF", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classG", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classK", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classL", Ontology::IS, Ontology::CLASS)
                                                                                 <<Triple("classA", Ontology::CONTAINS, "classB")
                                                                                 <<Triple("classB", Ontology::CONTAINS, "classC")
                                                                                 <<Triple("classB", Ontology::CONTAINS, "classD")
                                                                                 <<Triple("classF", Ontology::CONTAINS, "classG")
                                                                                 <<Triple("classG", Ontology::CONTAINS, "classK")
                                                                                 <<Triple("classG", Ontology::CONTAINS, "classL")
                                                                                 <<Triple("classA", Ontology::HAS_PROPERTY, "property1")
                                                                                 <<Triple("classB", Ontology::HAS_PROPERTY, "property2")
                                                                                 <<Triple("classC", Ontology::HAS_PROPERTY, "property3")
                                                                                 <<Triple("classD", Ontology::HAS_PROPERTY, "property4")
                                                                                 <<Triple("classF", Ontology::HAS_PROPERTY, "property5")
                                                                                 <<Triple("classG", Ontology::HAS_PROPERTY, "property6")
                                                                                 <<Triple("classK", Ontology::HAS_PROPERTY, "property7")
                                                                                 <<Triple("classL", Ontology::HAS_PROPERTY, "property8")
                                                                                 <<Triple("instance1", Ontology::IS, "classC")
                                                                                 <<Triple("instance2", Ontology::IS, "classD")
                                                                                 <<Triple("instance3", Ontology::IS, "classK")
                                                                                 <<Triple("instance4", Ontology::IS, "classL")
                                                                                 <<Triple("instance1", "property1", "value1")
                                                                                 <<Triple("instance2", "property2", "value2")
                                                                                 <<Triple("instance3", "property5", "value3")
                                                                                 <<Triple("instance4", "property6", "value4")))
                                                                    <<(MyHash()
                                                                       .insertIncMulti("property10", "value1")
                                                                       .insertIncMulti("property12", "value2")
                                                                       .insertIncMulti("property15", "value3")
                                                                       .insertIncMulti("property16", "value4"))
                                                                   <<(QSet<QString>()
                                                                      <<"instance1"
                                                                      <<"instance2"
                                                                      <<"instance3"
                                                                      <<"instance4");
}

void TOntology::TestInstancesForNonProperties()
{
    QFETCH(Ontology, ontology);
    QFETCH(MyHash, values);
    QFETCH(QSet<QString>, instances);

    QCOMPARE(ontology.instancesForNonProperties(values),instances);
}
