#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

#include "main.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    return 0;
}
