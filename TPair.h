#ifndef TPAIR_H

#define TPAIR_H

#include "Pair.h"

#include <QtTest/QtTest>

class TPair: public QObject
{
    Q_OBJECT
public:
    TPair();
private slots:
    //тесты
    void testEquals();
    void testEquals_data();

};

#endif // TPAIR_H
