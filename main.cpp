#include <QCoreApplication>

#include "TTriples.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    TTriplesStorage tTriplesStorage;
//    QTest::qExec(&tTriplesStorage);
    TTriples Ttriples;
    QTest::qExec(&Ttriples);


    return 0;
}
