#include "TOntologyBuilder.h"

TOntologyBuilder::TOntologyBuilder()
{
}

void TOntologyBuilder::TestAddClass_data()
{
    QTest::addColumn <Ontology> ("BuilderOntology");
    QTest::addColumn <Ontology> ("checkOntology");

    OntologyBuilder ontologyBuilder;
    ontologyBuilder.addClass("class1");

    Ontology checkOntology;
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);

    QTest::newRow("1 class")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class3");

    checkOntology.clearStorage();
    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class3", Ontology::IS, Ontology::CLASS);

    QTest::newRow("2 classes, 2 header")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();

    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class2", "class1");
    ontologyBuilder.addClass("class3", "class2");
    ontologyBuilder.addClass("class4", "class3");

    ontologyBuilder.addClass("class5");
    ontologyBuilder.addClass("class6", "class5");
    ontologyBuilder.addClass("class7", "class6");
    ontologyBuilder.addClass("class8", "class7");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class3", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class4", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class5", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class6", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class7", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class8", Ontology::IS, Ontology::CLASS);

    checkOntology.add("class1", Ontology::CONTAINS, "class2");
    checkOntology.add("class2", Ontology::CONTAINS, "class3");
    checkOntology.add("class3", Ontology::CONTAINS, "class4");

    checkOntology.add("class5", Ontology::CONTAINS, "class6");
    checkOntology.add("class6", Ontology::CONTAINS, "class7");
    checkOntology.add("class7", Ontology::CONTAINS, "class8");


    QTest::newRow("4 classes, 2 header")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();

    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class2", "class1");
    ontologyBuilder.addClass("class3", "class2");
    ontologyBuilder.addClass("class4", "class3");

    ontologyBuilder.addClass("class5");
    ontologyBuilder.addClass("class6", "class5");
    ontologyBuilder.addClass("class7", "class6");
    ontologyBuilder.addClass("class8", "class7");

    //фейковые записи которые не должны пройти (так как класс уже существует)
    ontologyBuilder.addClass("class7", "class6");
    ontologyBuilder.addClass("class8", "class7");
    //попытка создать класс с несуществующим предком
    ontologyBuilder.addClass("class9", "class10");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class3", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class4", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class5", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class6", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class7", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class8", Ontology::IS, Ontology::CLASS);

    checkOntology.add("class1", Ontology::CONTAINS, "class2");
    checkOntology.add("class2", Ontology::CONTAINS, "class3");
    checkOntology.add("class3", Ontology::CONTAINS, "class4");

    checkOntology.add("class5", Ontology::CONTAINS, "class6");
    checkOntology.add("class6", Ontology::CONTAINS, "class7");
    checkOntology.add("class7", Ontology::CONTAINS, "class8");


    QTest::newRow("4 classes, 2 header, fake classes in builder, fake masterclasses in builder")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class3");
    ontologyBuilder.addClass("class4", "class4");

    checkOntology.clearStorage();
    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class3", Ontology::IS, Ontology::CLASS);

    QTest::newRow("2 classes, 2 header, same masterclass and subclass in addClass")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

}

void TOntologyBuilder::TestAddClass()
{
    QFETCH(Ontology, BuilderOntology);
    QFETCH(Ontology, checkOntology);

    QCOMPARE(BuilderOntology, checkOntology);
}

void TOntologyBuilder::TestAddProperty_data()
{
    QTest::addColumn <Ontology> ("BuilderOntology");
    QTest::addColumn <Ontology> ("checkOntology");

    OntologyBuilder ontologyBuilder;
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addProperty("class1", "property1");

    Ontology checkOntology;
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::HAS_PROPERTY, "property1");

    QTest::newRow("1 class, 1 property")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addProperty("class1", "property1");
    ontologyBuilder.addProperty("class1", "property2");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::HAS_PROPERTY, "property1");
    checkOntology.add("class1", Ontology::HAS_PROPERTY, "property2");

    QTest::newRow("1 class, 2 properties")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    QTest::newRow("1 class, 1 property")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addProperty("class1", "property1");
    ontologyBuilder.addProperty("class1", "property2");

    ontologyBuilder.addClass("class2");
    ontologyBuilder.addProperty("class2", "property3");
    ontologyBuilder.addProperty("class2", "property4");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::HAS_PROPERTY, "property1");
    checkOntology.add("class1", Ontology::HAS_PROPERTY, "property2");

    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::HAS_PROPERTY, "property3");
    checkOntology.add("class2", Ontology::HAS_PROPERTY, "property4");

    QTest::newRow("2 class, 4 properties, 2 header")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class11", "class1");
    ontologyBuilder.addProperty("class11", "property1");
    ontologyBuilder.addProperty("class11", "property2");

    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class22", "class2");
    ontologyBuilder.addProperty("class22", "property3");
    ontologyBuilder.addProperty("class22", "property4");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class11", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::CONTAINS, "class11");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property1");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property2");

    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class22", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::CONTAINS, "class22");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property3");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property4");

    QTest::newRow("4 class, 4 properties, 2 header")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class11", "class1");
    ontologyBuilder.addProperty("class11", "property1");
    ontologyBuilder.addProperty("class111", "property2");

    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class22", "class2");
    ontologyBuilder.addProperty("class22", "property3");
    ontologyBuilder.addProperty("class222", "property4");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class11", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::CONTAINS, "class11");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property1");

    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class22", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::CONTAINS, "class22");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property3");

    QTest::newRow("2 class, 4 properties, 2 header, add property with fake class name")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class11", "class1");
    ontologyBuilder.addProperty("class11", "property1");
    ontologyBuilder.addProperty("class11", "property2");
    ontologyBuilder.addProperty("class1", "property2");


    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class22", "class2");
    ontologyBuilder.addProperty("class22", "property3");
    ontologyBuilder.addProperty("class222", "property4");
    ontologyBuilder.addProperty("class22", "property4");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class11", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::CONTAINS, "class11");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property1");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property2");

    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class22", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::CONTAINS, "class22");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property3");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property4");

    QTest::newRow("2 class, 4 properties, 2 header, add property adrealy exists")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

    ontologyBuilder.clearStorage();
    ontologyBuilder.addClass("class1");
    ontologyBuilder.addClass("class11", "class1");
    ontologyBuilder.addProperty("class11", "property1");
    ontologyBuilder.addProperty("class11", "property2");
    ontologyBuilder.addProperty("class1", "property2");


    ontologyBuilder.addClass("class2");
    ontologyBuilder.addClass("class22", "class2");
    ontologyBuilder.addProperty("class22", "property3");
    ontologyBuilder.addProperty("class222", "property4");
    ontologyBuilder.addProperty("class22", "property4");

    checkOntology.clearStorage();
    checkOntology.add("class1", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class11", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class1", Ontology::CONTAINS, "class11");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property1");
    checkOntology.add("class11", Ontology::HAS_PROPERTY, "property2");

    checkOntology.add("class2", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class22", Ontology::IS, Ontology::CLASS);
    checkOntology.add("class2", Ontology::CONTAINS, "class22");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property3");
    checkOntology.add("class22", Ontology::HAS_PROPERTY, "property4");

    QTest::newRow("2 class, 4 properties, 2 header, addproperty use fake class and add property adrealy exists")
            << (ontologyBuilder.getOntology())
            << (checkOntology);

}

void TOntologyBuilder::TestAddProperty()
{
    QFETCH(Ontology, BuilderOntology);
    QFETCH(Ontology, checkOntology);

    QCOMPARE(BuilderOntology, checkOntology);
}
