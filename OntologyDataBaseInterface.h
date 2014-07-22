#ifndef ONTOLOGYDATABASEINTERFACE_H
#define ONTOLOGYDATABASEINTERFACE_H
#include <QtSql>
class OntologyDataBaseInterface
{
public:
    OntologyDataBaseInterface(const QString &dataBaseName);
    void createTables();
    QString getDataBaseName();
private:
    QString dataBaseName_;
};

#endif // ONTOLOGYDATABASEINTERFACE_H
