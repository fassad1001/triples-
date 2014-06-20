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
    //нахожу максимально длинный список
    foreach (QString className, classNames)
    {
        muster += subjectsFor(Ontology().IS_VALUE, className);
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

QSet<QString> Ontology::allClasses() const
{
    return subjectsFor(Ontology().IS_VALUE, Ontology().CLASS_VALUE);
}

QSet<QString> Ontology::classesForInstance(const QString &instanceName) const
{
    return objectsFor(instanceName, Ontology().IS_VALUE);
}

QSet<QString> Ontology::classesForInstances(const QString &instanceNames) const
{
    QSet<QString> classes;
    //сбор всех возможных классов
    QSet<QString> musters;
    foreach(QString instanceName, instanceNames)
    {
        muster += classesForInstance(instanceName);
    }
    bool is_uniq = true;
    //перебираем образцы на предмет их одновременности нахождения в искомом
    foreach (QString muster, musters)
    {
        is_uniq = true;
        //по возможности помечаем элемент как неуникальный для двух элементов одновременно
        foreach(QString instanceName, instanceNames)
        {
            if (!classesForInstance(instanceName).contains(muster))
            {
                is_uniq = false;
            }
        }
        //если элемент после проверки остался уникальным для всего перебранного то записываем его
        //как удавшийся, то есть в результат
        if (is_uniq == true)
        {
            classes += muster;
        }
    }
    return classes;
}

QSet<QString> Ontology::subClasses(const QString &className) const
{
    //подклассы className
    return objectsFor(className, Ontology().CONTAINS_VALUE);
}

QSet<QString> Ontology::superClasses(const QString &className) const
{
    return subjectsFor(Ontology().CONTAINS_VALUE, className);
}


