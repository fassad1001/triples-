#include "BenchmarkResult.h"

BenchmarkResult::BenchmarkResult()
{
}

void BenchmarkResult::setTime(const QString &methodName, const QString &dataName, const int &time)
{
    table_[dataName][methodName] = time;
    methodNames_ << methodName;
}

QString BenchmarkResult::toString() const
{
    QStringList header;
    QStringList rows;

    foreach(const QString &data, table_.keys())
    {
        header << data;
    }
    rows << ("\n ;" + header.join(";"));
    foreach(const QString &method, methodNames_)
    {
        QStringList cells;
        cells << method;
        foreach(const QString &data, table_.keys())
        {
            cells << QString::number(table_[data][method]);
        }
        rows << cells.join(";");
    }

    return rows.join("\n");
}

void BenchmarkResult::writeFile(const QString &fileName) const
{
    QFile data(fileName);
    if(data.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QTextStream stream(&data);

        stream << toString();

        data.close();
    }
}
