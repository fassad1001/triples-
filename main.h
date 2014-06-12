#ifndef MAIN_H

#define MAIN_H
#include <QtTest/QtTest>

inline uint qHash(const Triple &triple)
{
    return qHash(triple.toString());
}

#endif // MAIN_H
