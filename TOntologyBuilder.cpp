#include "TOntologyBuilder.h"

TOntologyBuilder::TOntologyBuilder()
{
}

void TOntologyBuilder::TestAddClass_data()
{
    QTest::addColumn <OntologyBuilder> ("initOntology");
    QTest::addColumn <QString> ("className");
    QTest::addColumn <QString> ("parentClassName");
    QTest::addColumn <Ontology> ("expectedOntology");

    QTest::newRow("1 class, 1 header class")
            << (OntologyBuilder())
            << ("class1")
            << (QString())
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)));

    QTest::newRow("2 class 2 header class")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class2", Ontology::IS, Ontology::CLASS)))
            << ("class3")
            << (QString())
            << (Ontology(QSet<Triple>()
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)));

    QTest::newRow("2 class 2 header class inheritance")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class2", Ontology::IS, Ontology::CLASS)))
            << ("class3")
            << ("class2")
            << (Ontology(QSet<Triple>()
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)
                         <<Triple("class3", Ontology::IS, Ontology::CLASS)
                         <<Triple("class2", Ontology::CONTAINS, "class3")));

    QTest::newRow("2 class 2 header class fake inheritance class")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class2", Ontology::IS, Ontology::CLASS)))
            << ("class3")
            << ("class12")
            << (Ontology(QSet<Triple>()
                         <<Triple("class2", Ontology::IS, Ontology::CLASS)));

    QTest::newRow("2 class 2 header class, subclass adrealy exists")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class2", Ontology::IS, Ontology::CLASS)
                                << Triple("class4", Ontology::IS, Ontology::CLASS)))
            << ("class2")
            << ("class4")
            << (Ontology(QSet<Triple>()
                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                         << Triple("class4", Ontology::IS, Ontology::CLASS)));

    QTest::newRow("2 class 2 header class, subclass adrealy exists and fake inheritance class")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class2", Ontology::IS, Ontology::CLASS)
                                << Triple("class4", Ontology::IS, Ontology::CLASS)))
            << ("class2")
            << ("class41")
            << (Ontology(QSet<Triple>()
                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                         << Triple("class4", Ontology::IS, Ontology::CLASS)));


}

void TOntologyBuilder::TestAddClass()
{
    QFETCH(OntologyBuilder, initOntology);
    QFETCH(QString, className);
    QFETCH(QString, parentClassName);
    QFETCH(Ontology, expectedOntology);

    initOntology.addClass(className, parentClassName);

    QCOMPARE(initOntology.getOntology(), expectedOntology);
}

void TOntologyBuilder::TestAddProperty_data()
{

    QTest::addColumn <OntologyBuilder> ("initOntology");
    QTest::addColumn <QString> ("className");
    QTest::addColumn <QString> ("propertyName");
    QTest::addColumn <Ontology> ("expectedOntology");

    QTest::newRow("empty OntologyBuilder, 1 property")
            << (OntologyBuilder(QSet<Triple>()))
            << ("class1")
            << ("property1")
            << (Ontology(QSet<Triple>()));

    QTest::newRow("1 class, 1 property")
            << (OntologyBuilder(QSet<Triple>()
                               << Triple("class1", Ontology::IS, Ontology::CLASS)))
            << ("class1")
            << ("property1")
            << (Ontology(QSet<Triple>()
                        << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("class1", Ontology::HAS_PROPERTY, "property1")));

    QTest::newRow("1 class, 2 property")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property1")))
            << ("class1")
            << ("property2")
            << (Ontology(QSet<Triple>()
                        << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         << Triple("class1", Ontology::HAS_PROPERTY, "property2")));


    QTest::newRow("1 class, 2 property fake className")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property2")))
            << ("class21")
            << ("property3")
            << (Ontology(QSet<Triple>()
                        << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         << Triple("class1", Ontology::HAS_PROPERTY, "property2")));

    QTest::newRow("1 class, 2 property, existing property name")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                << Triple("class2", Ontology::IS, Ontology::CLASS)
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property2")))
            << ("class2")
            << ("property1")
            << (Ontology(QSet<Triple>()
                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                          << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                          << Triple("class1", Ontology::HAS_PROPERTY, "property2")));

    QTest::newRow("1 class, 2 property, existing property name")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                << Triple("class2", Ontology::IS, Ontology::CLASS)
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                 << Triple("class1", Ontology::HAS_PROPERTY, "property2")))
            << ("class12")
            << ("property1")
            << (Ontology(QSet<Triple>()
                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("class2", Ontology::IS, Ontology::CLASS)
                          << Triple("class1", Ontology::HAS_PROPERTY, "property1")
                          << Triple("class1", Ontology::HAS_PROPERTY, "property2")));
}

void TOntologyBuilder::TestAddProperty()
{
    QFETCH(OntologyBuilder, initOntology);
    QFETCH(QString, className);
    QFETCH(QString, propertyName);
    QFETCH(Ontology, expectedOntology);

    initOntology.addProperty(className, propertyName);

    QCOMPARE(initOntology.getOntology(), expectedOntology);
}

void TOntologyBuilder::TestAddInstance_data()
{
    QTest::addColumn <OntologyBuilder> ("initOntology");
    QTest::addColumn <QString> ("className");
    QTest::addColumn <QString> ("instanceName");
    QTest::addColumn <Ontology> ("expectedOntology");

    QTest::newRow("empty ontologyBuilder")
            << (OntologyBuilder(QSet<Triple>()))
            << ("class1")
            << ("instance1")
            << (Ontology(QSet<Triple>()));

    QTest::newRow("1 class, 1 instance")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)))
            << ("class1")
            << ("instance1")
            << (Ontology(QSet<Triple>()
                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("instance1", Ontology::IS, "class1")));

    QTest::newRow("1 class, 2 instance")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                << Triple("instance1", Ontology::IS, "class1")))
            << ("class1")
            << ("instance2")
            << (Ontology(QSet<Triple>()
                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("instance1", Ontology::IS, "class1")
                         << Triple("instance2", Ontology::IS, "class1")));

    QTest::newRow("1 class, 2 instance, fake class")
            << (OntologyBuilder(QSet<Triple>()
                                << Triple("class1", Ontology::IS, Ontology::CLASS)
                                << Triple("instance1", Ontology::IS, "class1")))
            << ("class12")
            << ("instance2")
            << (Ontology(QSet<Triple>()
                         << Triple("class1", Ontology::IS, Ontology::CLASS)
                         << Triple("instance1", Ontology::IS, "class1")));

}

void TOntologyBuilder::TestAddInstance()
{
    QFETCH(OntologyBuilder, initOntology);
    QFETCH(QString, className);
    QFETCH(QString, instanceName);
    QFETCH(Ontology, expectedOntology);

    initOntology.addInstance(className, instanceName);

    QCOMPARE(initOntology.getOntology(), expectedOntology);
}

void TOntologyBuilder::TestSetPropertyValue_data()
{
    QTest::addColumn <OntologyBuilder> ("initOntology");
    QTest::addColumn <QString> ("instanceName");
    QTest::addColumn <QString> ("propertyName");
    QTest::addColumn <QString> ("value");
    QTest::addColumn <Ontology> ("expectedOntology");

    QTest::newRow("empty ontologyBuilder")
            << (OntologyBuilder(QSet<Triple>()))
            << ("instance1")
            << ("property1")
            << ("value1")
            << (Ontology(QSet<Triple>()));

    QTest::newRow("1 class, 1 property, 1 instance, 1 value")
            << (OntologyBuilder(QSet<Triple>()
                                <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                <<Triple("instance1", Ontology::IS, "class1")))
            << ("instance1")
            << ("property1")
            << ("value1")
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         <<Triple("instance1", Ontology::IS, "class1")
                         <<Triple("instance1", "property1", "value1")));

    QTest::newRow("1 class, 1 property, 1 instance, new value")
            << (OntologyBuilder(QSet<Triple>()
                                <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                <<Triple("instance1", Ontology::IS, "class1")
                                <<Triple("instance1", "property1", "value1")))
            << ("instance1")
            << ("property1")
            << ("value2")
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         <<Triple("instance1", Ontology::IS, "class1")
                         <<Triple("instance1", "property1", "value2")));

    QTest::newRow("1 class, 1 property, 1 instance, fake instance name")
            << (OntologyBuilder(QSet<Triple>()
                                <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                <<Triple("instance1", Ontology::IS, "class1")))
            << ("instance2")
            << ("property1")
            << ("value1")
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         <<Triple("instance1", Ontology::IS, "class1")));

    QTest::newRow("1 class, 1 property, 1 instance, fake property name")
            << (OntologyBuilder(QSet<Triple>()
                                <<Triple("class1", Ontology::IS, Ontology::CLASS)
                                <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                                <<Triple("instance1", Ontology::IS, "class1")))
            << ("instance1")
            << ("property2")
            << ("value1")
            << (Ontology(QSet<Triple>()
                         <<Triple("class1", Ontology::IS, Ontology::CLASS)
                         <<Triple("class1", Ontology::HAS_PROPERTY, "property1")
                         <<Triple("instance1", Ontology::IS, "class1")));
}

void TOntologyBuilder::TestSetPropertyValue()
{
    QFETCH(OntologyBuilder, initOntology);
    QFETCH(QString, instanceName);
    QFETCH(QString, propertyName);
    QFETCH(QString, value);
    QFETCH(Ontology, expectedOntology);

    initOntology.setPropertyValue(instanceName, propertyName, value);

    QCOMPARE(initOntology.getOntology(), expectedOntology);
}
