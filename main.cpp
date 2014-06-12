#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

#include "main.h"

int main(int argc, char *argv[])
{
    // этот гадёныш всегда ноль возвращает! =(
    //    qWarning()<<(QCryptographicHash::hash(QByteArray().append("fewfdwfds"),QCryptographicHash::Sha256).toUInt());
    qWarning()<<qHash(Triple("1","5","fdsfsd"));

    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    return 0;
}
