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
    void TestEquals_data();
    void TestEquals();

};

#endif // TPAIR_H
