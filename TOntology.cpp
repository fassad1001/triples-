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
    
}

void TOntology::TestAnyClassInstances_data()
{
    
}

void TOntology::TestAllClassInstances()
{
    
}

void TOntology::TestAllClassInstances_data()
{
    
}
