#ifndef TONTOLOGYDATABASEINTERFACE_H

#define TONTOLOGYDATABASEINTERFACE_H

#include "OntologyDataBaseInterface.h"

#include <QtTest/QtTest>

class TOntologyDataBaseInterface: public QObject
{
    Q_OBJECT
public:
    TOntologyDataBaseInterface();
private slots:
    //методы для тестирования
    void TestOntologyDataBaseInterface_data();
    void TestOntologyDataBaseInterface();

};

#endif // TONTOLOGYDATABASEINTERFACE_H
