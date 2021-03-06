#ifndef ONTOLOGYDATABASEINTERFACE_H
#define ONTOLOGYDATABASEINTERFACE_H
#include <QtSql>
class OntologyDataBaseInterface
{
public:
    OntologyDataBaseInterface(const QString &dataBaseName);
    void createTables();
    QHash<int, QString> getNames();
    QString getDataBaseName();
    bool isExists(const QString &ontologyName);
    QHash<int, QString> getOntologyNames();
private:
    QString dataBaseName_;
};

#endif // ONTOLOGYDATABASEINTERFACE_H
