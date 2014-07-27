#ifndef ONTOLOGYDATABASEINTERFACE_H
#define ONTOLOGYDATABASEINTERFACE_H
#include <QtSql>
class OntologyDataBaseInterface
{
public:
    OntologyDataBaseInterface(const QString &dataBaseName);

    void createTables();

    bool isExists(const QString &ontologyName);

    QHash<int, QString> getNames();
    QHash<int, QString> getOntologyNames();

    QString getDataBaseName();

    QSqlQuery getQuery(const QString &fileName);
    QSqlDatabase getDataBase(const QString &fileName);
private:
    QString dataBaseName_;
};

#endif // ONTOLOGYDATABASEINTERFACE_H
