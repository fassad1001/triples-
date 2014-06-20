#include "Ontology.h"

Ontology::Ontology() :
    IS_VALUE("is"),
    CONTAINS_VALUE("contains"),
    CLASS_VALUE("class")
{
}

Ontology::Ontology(QSet<Triple> storage) :
    TripleStorage(storage)
{
}

QSet<QString> Ontology::classInstances(const QString &className) const
{
    return subjectsFor(Ontology().IS_VALUE, className);
}

QSet<QString> Ontology::anyClassInstances(const QStringList &classNames) const
{
    QSet<QString> instanses;
    foreach (QString className, classNames)
    {
        instanses += classInstances(className);
    }
    return instanses;
}

QSet<QString> Ontology::allClassInstances(const QStringList &classNames) const
{
    //все экземпляры, которые входят в каждый класс из classNames
    QSet<QString> muster;
    QSet<QString> instanses;
    int length = subjectsFor(Ontology().IS_VALUE, classNames.at(0)).size();
    //нахожу максимально длинный список
    foreach (QString className, classNames)
    {
        if (subjectsFor(Ontology().IS_VALUE, className).size() > length)
        {
            muster = subjectsFor(Ontology().IS_VALUE, className);
        }
    }
    bool is_uniq;
    //иду по всем элементам образца
    foreach (QString musterElement, muster)
    {
        is_uniq = true;
        //для элемента образца ставлю метку если он не присутствует хотябы в одном списке
        foreach (QString className, classNames)
        {
            if (!subjectsFor(Ontology().IS_VALUE, className).contains(musterElement))
            {
                is_uniq = false;
            }
        }
        //в случае отсутствия изменения метки я записываю элемент образца в результат
        if (is_uniq == true)
        {
            instanses << musterElement;
        }
    }
    return instanses;
}


