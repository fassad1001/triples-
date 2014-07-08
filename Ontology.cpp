#include "Ontology.h"

const QString Ontology::IS = "is";
const QString Ontology::CONTAINS = "contains";
const QString Ontology::CLASS = "class";

Ontology::Ontology()
{
}

Ontology::Ontology(QSet<Triple> storage) :
    TripleStorage(storage)
{
}

QSet<QString> Ontology::classInstances(const QString &className) const
{
    QSet<QString> classesForCicle;
    QSet<QString> resultInstances;
    QSet<QString> classesForRes;
    classesForCicle += className;
    resultInstances += subjectsFor(Ontology::IS, className);
    while(!classesForCicle.empty())
    {
        foreach(const QString classForCicle, classesForCicle)
        {
            foreach(const QString classf, subClasses(classForCicle))
            {
                resultInstances += subjectsFor(Ontology::IS, classf);
            }
            classesForCicle = subClasses(classForCicle);
        }
    }
    return resultInstances;
}

QSet<QString> Ontology::anyClassInstances(const QStringList &classNames) const
{
    QSet<QString> instanses;
    foreach(const QString &className, classNames)
    {
        instanses += classInstances(className);
    }
    return instanses;
}

QSet<QString> Ontology::allClassInstances(const QStringList &classNames) const
{
    // !!! ПЕРЕПИСАТЬ ИСПОЛЬЗУЯ ОПЕРАТОР ПЕРЕСЕЧЕНИЯ МНОЖЕСТВ И МЕТОД classInstances

    //все экземпляры, которые входят в каждый класс из classNames
    QSet<QString> muster;
    QSet<QString> instanses;
    //нахожу максимально длинный список
    foreach(const QString className, classNames)
    {
        muster += subjectsFor(Ontology::IS, className);
    }
    bool is_uniq;
    //иду по всем элементам образца
    foreach(const QString musterElement, muster)
    {
        is_uniq = true;
        //для элемента образца ставлю метку если он не присутствует хотябы в одном списке
        foreach(const QString className, classNames)
        {
            if (!subjectsFor(Ontology::IS, className).contains(musterElement))
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
    return subjectsFor(Ontology::IS, Ontology::CLASS);
}

QSet<QString> Ontology::allInstances() const
{
    // !!!! ИЗНАЧАЛЬНО ПОЛУЧИТЬ МНОЖЕСТВО ВСЕХ КЛАССОВ И С ПОМЩЬЮ НЕГО ПРОВЕРЯТЬ ЯВЛЯЕТСЯ ЛИ ОБЪЕКТ КЛАССОМ
    QSet<QString> instances;
    QSet<QString> classes = allClasses();
    foreach(const QString classItem, classes)
    {
        foreach(const QString instance, subjectsFor(Ontology::IS, classItem))
        {
            instances += instance;
        }
    }
    return instances;
}

QSet<QString> Ontology::classesForInstance(const QString &instanceName) const
{
    return objectsFor(instanceName, Ontology::IS);
}

QSet<QString> Ontology::subClasses(const QString &className) const
{
    return objectsFor(className, Ontology::CONTAINS);
    QSet<QString> result;
    QSet<QString> loopClasses;
    QSet<QString> exchangeClasses;
    loopClasses += className;
    result += objectsFor(className, Ontology::CONTAINS);
    while (!loopClasses.empty())
    {
        exchangeClasses.clear();
        foreach(QString loopclass, loopClasses)
        {
            QSet<QString> subjectsTooLoop = subjectsFor(Ontology::CONTAINS, loopclass);
            foreach (const QString loopClass, subjectsTooLoop)
            {
                result += objectsFor(loopClass, Ontology::CONTAINS);
                exchangeClasses += objectsFor(loopClass, Ontology::CONTAINS);
            }
            loopClasses = exchangeClasses;
        }
    }

}

QSet<QString> Ontology::superClasses(const QString &className) const
{
    QSet<QString> result;
    QSet<QString> loopClasses;
    QSet<QString> exchangeClasses;
    loopClasses += className;
    result += subjectsFor(Ontology::CONTAINS, className);
    while (!loopClasses.empty())
    {
        exchangeClasses.clear();
        foreach (const QString loopClass, subjectsFor(Ontology::CONTAINS, loopClasses))
        {
            result += subjectsFor(Ontology::CONTAINS, loopClass);
            exchangeClasses =+ subjectsFor(Ontology::CONTAINS, loopClass);
        }
        loopClasses = exchangeClasses;
    }
    return result;
}



QSet<QString> Ontology::mainSuperClass(const QString &instanceName1, const QString &instanceName2) const
{
    // ПОЛУЧИТЬ ВСЕ КЛАССЫ ДЛЯ instanceName1 И instanceName2, НАЙТИ ИХ ПЕРЕСЕЧЕНИЕ, В ПЕРЕСЕЧЕНИИ НАЙТИ МИНИМАЛЬНЫЕ КЛАССЫ ЧЕРЕЗ ФУНКЦИЮ qSort
    QList InterSectionClasses = classesForInstance(instanceName1) & classesForInstance(instanceName2);
    qSort(InterSectionClasses.begin(), InterSectionClasses.end(), CompareClassesMainSuper);
    return InterSectionClasses.first();
    QSet<QStriing> result;
    foreach(QString intersectionClass, InterSectionClasses)
    {
        if (intersectionClass == InterSectionClasses.first())
        {
            result += intersectionClass;
        }
    }
    return result;
}

int Ontology::CompareClassesMainSuper(const QString &className1, const QString &className2) const
{
    if(superClasses(className1_)==superClasses(className2))
    {
        return 0;
    }
    if(superClasses(className1_)<superClasses(className2))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int Ontology::CompareByClassLvl(const QString &className1, const QString &className2) const
{
    if(getClassLvl(className1) > getClassLvl(className2))
    {
        return 1;
    }
    if(getClassLvl(className1) == getClassLvl(className2))
    {
        return 0;
    }
    if(getClassLvl(className1) < getClassLvl(className2))
    {
        return -1;
    }
}

bool Ontology::isValid() const
{
    QSet<QString> classes = allClasses();
    QSet<QString> loopclasses = allClasses();
    QSet<Pair> transitiveClosure = subjectsAndObjects(Ontology::CONTAINS);
    foreach(QString Class, classes)
    {
        foreach(QString loopclass, loopclasses)
        {
            if (subClasses(Class).contains(loopclass))
            {
                transitiveClosure += Pair(Class, loopclass);
            }
        }
    }
    foreach(Pair transitiveClosureItem, transitiveClosure)
    {
        if(transitiveClosure.contains(Pair(transitiveClosureItem.second(), transitiveClosureItem.first()))
                && transitiveClosure.contains(Pair(transitiveClosureItem.first(), transitiveClosureItem.first())))
        {
            return true;
        }
    }
}
bool Ontology::isMinimal() const
{
    QSet<QString> allinstances = allInstances();
    //посмотреть все инстансы, для каждого смотрю классы и подклассы, если один из этих наборов
    //содержит инстанс то возвращаю правду иначен ложь
    foreach(QString instance, allinstances)
    {
        QString instanceClass = classesForInstance(instance);
        if(subClasses(instanceClass).contains(instance) || superClasses(instanceClass).contains(instance))
        {
            return true;
        }
    }
}


int Ontology::getClassLvl(const QString &className) const
{
    QSet<QString> headerClasses;
    QSet<QString> classes = allClasses();
    foreach(const QString classf, classes)
    {
        if (superClasses(classf).empty())
        {
            headerClasses += classf;
        }
    }
    QSet<QString> classesForCycle = headerClasses;
    QSet<QString> classesForTest;
    int level = 0;
    if (classesForCycle.contains(className))
    {
        return level;
    }
    level ++;
    while(!classesForCycle.empty())
    {

        foreach(const QString classf, classesForCycle)
        {
            classesForTest += subClasses(classf);
        }
        if (classesForTest.contains(className))
        {
            return level;
        }
        level ++;
        classesForTest.clear();
        foreach(const QString classf, classesForCycle)
        {
            classesForCycle += subClasses(classf);
        }
    }
    return -1;
}

QSet<QString> Ontology::getNotMinimalInstances() const
{
    QSet<QString> instances = allInstances();
    QSet<QString> classesforinstance;
    foreach(QString instance, instances)
    {
        classesforinstance = classesForInstance(instance);
        //у нас могут быть как и те которые находятся на одной ветке так и те которые находятся на разных ветках
        //отсеиваем их по веткам
        //каждый класс - потенциально новая ветка
        foreach(const QString classforinstance, classesforinstance)
        {
            QList<QString> branch = subClasses(classforinstance) + superClasses(classforinstance);
            QList<QString> branchItemsWithInstance;
            branchItemsWithInstance.clear();
            foreach(const QString branchItem, branch)
            {
                //если класс ветви содержит сущность которую мы ищем
                if(classInstances(branchItem).contains(instance))
                {
                    //то добавляем этот класс в коллекцию на конкурс
                    return false;
                }
        }
    }
}

void Ontology::minimalize()
{
    QSet<QString> instances = allInstances();
    QSet<QString> classesforinstance;
    foreach(QString instance, instances)
    {
        classesforinstance = classesForInstance(instance);
        //у нас могут быть как и те которые находятся на одной ветке так и те которые находятся на разных ветках
        //отсеиваем их по веткам
        //каждый класс - потенциально новая ветка
        foreach(const QString classforinstance, classesforinstance)
        {
            QList<QString> branch = subClasses(classforinstance) + superClasses(classforinstance);
            QList<QString> branchItemsWithInstance;
            branchItemsWithInstance.clear();
            foreach(const QString branchItem, branch)
            {
                //если класс ветви содержит сущность которую мы ищем
                if(classInstances(branchItem).contains(instance))
                {
                    //то добавляем этот класс в коллекцию на конкурс
                    branchItemsWithInstance += branchItem;
                }
            }
            //собираю элементы ветки для перебора
            QList<QString> branchItemstoLoop = branchItemsWithInstance;
            //сортирую по увеличению значения уровень иерархии
            qSort(branchItemsWithInstance.begin(), branchItemsWithInstance.end(), CompareByClassLvl);
            //убираю элемент с минмальным уровнем иерархии из списка на чистку
            branchItemstoLoop -= branchItemsWithInstance.first();
            //провожу чистку удаляю тройки со значениями (instance IS itemToRemove)
            foreach(const QString ItemToRemove, branchItemstoLoop)
            {
                triples_ -= Triple(instance, Ontology::IS, ItemToRemove);
            }
        }
    }
}

bool Ontology::operator ==(const Ontology &o) const
{
    return triples_ == o.triples_;
}


