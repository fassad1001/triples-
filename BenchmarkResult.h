#ifndef BENCHMARKRESULT_H

#define BENCHMARKRESULT_H

#include <QtCore>

class BenchmarkResult
{
public:
    BenchmarkResult();

    void setTime(const QString &methodName, const QString &dataName, const int &time);

    QString toString() const;

    void writeFile(const QString &fileName) const;

private:
    QHash<QString, QHash<QString, int> > table_;
    QSet<QString> methodNames_;
};

#endif // BENCHMARKRESULT_H
