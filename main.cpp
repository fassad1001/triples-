#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

#include "TPair.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    TPair pair;
    QTest::qExec(&pair);

    return 0;
}
