#ifndef TTRIPLES_H

#define TTRIPLES_H

#include <QtTest/QtTest>

#include "Triple.h"

class TTriples : public QObject
{
    Q_OBJECT
public:
    TTriples();
private slots:
    //тесты
    void testToString();
    void testToString_data();

    void testQhash();
    void testQhash_data();

    void testOperatorEquals();
    void testOperatorEquals_data();
};

#endif // TTRIPLES_H
