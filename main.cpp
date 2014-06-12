#include <QCoreApplication>

#include <QCryptographicHash>

#include "TTriples.h"

inline uint qHash(const Triple &triple)
{
    return (QCryptographicHash::hash(QByteArray().append(triple.toString()),QCryptographicHash::Sha3_384).toUInt());
}

int main(int argc, char *argv[])
{
    // этот гадёныш всегда ноль возвращает! =(
//    qWarning()<<(QCryptographicHash::hash(QByteArray().append("fewfdwfds"),QCryptographicHash::Sha256).toUInt());

    QCoreApplication a(argc, argv);

    TTriples Ttriples;
    QTest::qExec(&Ttriples);

    return 0;
}
