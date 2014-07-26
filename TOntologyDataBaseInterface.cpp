#include "TOntologyDataBaseInterface.h"

TOntologyDataBaseInterface::TOntologyDataBaseInterface()
{
}

void TOntologyDataBaseInterface::TestOntologyDataBaseInterface_data()
{
    QTest::addColumn <QString> ("dbFileName");

    QTest::newRow("new DB1") << "testDB1.db";
    QTest::newRow("create again1") << "testDB.db1";
    QTest::newRow("new DB1") << "testDB2.db";
    QTest::newRow("create again1") << "testDB2.db";
}

void TOntologyDataBaseInterface::TestOntologyDataBaseInterface()
{
    //входные данные это имя_файла
    QFETCH(QString, dbFileName);
    bool testIsOk;
    //проверяю БД на наличие
    if(QFile::exists(dbFileName))
    {
        //пытаюсь удалить и если не получается
        if(!QFile::remove(dbFileName))
        {
            //тест падает
            QFAIL("не могу удалить файл БД");
        }
    }
    //создаю БД
    OntologyDataBaseInterface interface = OntologyDataBaseInterface(dbFileName);
    //проверяю БД на существование
    if(QFile::exists(dbFileName))
    {
        //тест пройден
        testIsOk = true;
    }
    else
    {
        //тест не пройден
        QFAIL("файл БД не был создан");
    }

    //если ошибок не было и БД была создана тест пройден
    //сравниваемые данные это то чему равна переменная проверки результата и true
    QCOMPARE(testIsOk, true);
}
