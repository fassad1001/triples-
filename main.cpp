#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

#include "TPair.h"

#include "TTripleStorage.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    TPair pair;
    QTest::qExec(&pair);

    TTripleStorage TtripleStorage;
    QTest::qExec(&TtripleStorage);

    return 0;
}
