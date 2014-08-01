#ifndef ONTOLOGYDATABASEINTERFACE_H

#define ONTOLOGYDATABASEINTERFACE_H

#include <QtSql>

#include "Ontology.h"

class OntologyDataBaseInterface
{
public:
    OntologyDataBaseInterface(const QString &dataBaseName);

    bool isExists(const QString &ontologyName);

    QSet<QString> getOntologys();
protected:
    QSqlQuery getQuery(const QString &fileName);
    QSqlDatabase getDataBase(const QString &fileName);

    QString getDataBaseName();

    QHash<int, QString> getNames();
    QHash<int, QString> getOntologyNames();

    void createTables();
    static QHash<QString, QString> systemValueUserValue;

private:
    QString dataBaseName_;
};

#endif // ONTOLOGYDATABASEINTERFACE_H
