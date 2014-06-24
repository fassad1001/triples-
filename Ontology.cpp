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

QSet<QString> Ontology::allInstances() const
{
    QSet<QString> instances;
    QSet<Pair> a = subjectsAndObjects(Ontology().IS_VALUE);
    foreach (Pair p, a)
    {
        if (p.second() != Ontology().CLASS_VALUE
        && contains(Triple(p.second(), Ontology().IS_VALUE, Ontology().CLASS_VALUE)))
        {
            instances << p.first();
        }
    }
    return instances;
}

QSet<QString> Ontology::classesForInstance(const QString &instanceName) const
{
    return objectsFor(instanceName, Ontology().IS_VALUE);
}

QSet<QString> Ontology::classesForInstances(const QStringList &instanceNames) const
{
    QSet<QString> classes;
    //сбор всех возможных классов
    QSet<QString> musters;
    foreach(QString instanceName, instanceNames)
    {
        musters += classesForInstance(instanceName);
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

QSet<QString> Ontology::mainSuperClass(const QString &instanceName1, const QString &instanceName2) const
{
    int minSuper;
    bool minIsSet;
    QStringList instances;
    QSet<QString> minimalClass;
    //подготовил элементы для выбора общих классов
    instances<<instanceName1<<instanceName2;
    //установил метку "минимум установлен" на ложь
    minIsSet = false;
    //перебираю все классы которые являются общими для набора элементов
    QSet<QString> classes;
    classes = classesForInstances(instances);
    foreach (QString class_, classes)
    {
        if (!minIsSet)
        {
            minSuper = superClasses(class_).size();
            minIsSet = true;
        }
        //если у интересующего нас класса меньше суперклассов то это хорошо то мы запоминаем это число
        //и запоминаем этот класс
        if (superClasses(class_).size() < minSuper)
        {
            minSuper = superClasses(class_).size();
            minimalClass = QSet<QString>() << class_;
        }
    }
    foreach (QString class_, classes)
    {
        if (superClasses(class_).size() == minSuper)
        {
            minSuper = superClasses(class_).size();
            minimalClass << class_;
        }
    }
    return minimalClass;
}

QSet<QString> Ontology::mainSuperClass(const QStringList &instances) const
{
    int minSuper;
    bool minIsSet;
    QSet<QString> minimalClass;
    //установил метку "минимум установлен" на ложь
    minIsSet = false;
    //перебираю все классы которые являются общими для набора элементов
    QSet<QString> classes;
    classes = classesForInstances(instances);
    foreach (QString class_, classes)
    {
        if (!minIsSet)
        {
            minSuper = superClasses(class_).size();
            minIsSet = true;
        }
        //если у интересующего нас класса меньше суперклассов то это хорошо то мы запоминаем это число
        //и запоминаем этот класс
        if (superClasses(class_).size() < minSuper)
        {
            minSuper = superClasses(class_).size();
            minimalClass = QSet<QString>() << class_;
        }
    }
    foreach (QString class_, classes)
    {
        if (superClasses(class_).size() == minSuper)
        {
            minSuper = superClasses(class_).size();
            minimalClass << class_;
        }
    }
    return minimalClass;
}

bool Ontology::isValid() const
{
    QSet<QString> classes = allClasses();
    //ищу вершинки на выходе получаю список вершинок определенного уровня
    bool hasEnd;
    QSet<QString> levelItems;
    hasEnd = false;
    foreach (QString class__, classes)
    {
        foreach (QString class_, subClasses(class__))
        {
            if (subClasses(class_).contains(class__))
            {
                return false;
            }
        }
        //если это верхний класс в иерархии
        if (superClasses(class__).size() == 0)
        {
            //запоминаем его как элемент набора верхних классов
            levelItems += class__;
        }
        else
        {
            hasEnd = true;
        }
    }
    if (hasEnd)
    {
        return true;
    }
    return isValid(levelItems);

}

bool Ontology::isValid(const QSet<QString> checkClasses) const
{
    QSet<QString> classes_next;
    bool hasEnd;
    hasEnd = false;
    foreach (QString class__, checkClasses)
    {
        //если есть подклассы
        if(subClasses(class__).size() != 0)
        {
            //для каждого подкласса делаю проверку
            foreach (QString class_, subClasses(class__))
            {
                if (subClasses(class_).contains(class__))
                {
                    return false;
                }
            }
            classes_next += subClasses(class__);
        }
        else
        {
            hasEnd = true;
        }
    }
    if (hasEnd)
    {
        return true;
    }
    return isValid(classes_next);

}

bool Ontology::isMinimal() const
{
    QSet<QString> allinstances = allInstances();
    foreach (QString instance, allinstances)
    {
        QSet<QString> instanceClasses = classesForInstance(instance);
        foreach (QString instanceClass, instanceClasses)
        {
           if (!subClasses(instanceClass).empty())
           {
               foreach (QString subclass, subClasses(instanceClass))
               {
                   if (classesForInstance(instance).contains(subclass))
                   {
                       return false;
                   }
               }
           }

           if (!superClasses(instanceClass).empty())
           {
               foreach (QString superclass, superClasses(instanceClass))
               {
                   if (classesForInstance(instance).contains(superclass))
                   {
                       return false;
                   }
               }
           }
        }

        const bool minimalDown = isMinimalDown(instance, classesForInstance(instance));
        const bool minimalUp = isMinimalUp(instance, classesForInstance(instance));


        if (!minimalDown || !minimalUp)
        {
            return false;
        }
        else
        {
            return true;
        }
        //для каждого смотрим его класс и для этого класса смотрим все его подклассы для каждого подкласса
        //просматриваем наличие инстанса и если этот тот инстанс то возарвщаем ложь иначе возвращаем правду

        //для каждого смотри его класс и если у класса есть суперклассы то мы смотрим есть ли у суперкласса
        //просматриваем наличие инстанса и если этот тот инстанс то возарвщаем ложь иначе возвращаем правду
    }
}

bool Ontology::isMinimalUp(const QString &instance, const QSet<QString> &levelItems) const
{
    QSet<QString> classes_next;
    bool hasEnd;
    hasEnd = false;
    foreach (QString class__, levelItems)
    {
        //если есть подклассы
        if(!superClasses(class__).empty())
        {
            if ((superClasses(class__) + classesForInstance(instance)).size()
                    < superClasses(class__).size() + classesForInstance(instance).size())
            {
                return false;
            }
            classes_next += superClasses(class__);
        }
        else
        {
            hasEnd = true;
        }
    }
    if (hasEnd)
    {
        return true;
    }
    return isMinimalUp(instance, classes_next);
}

bool Ontology::isMinimalDown(const QString &instance, const QSet<QString> &levelItems) const
{
    QSet<QString> classes_next;
    bool hasEnd;
    hasEnd = false;
    foreach (QString class__, levelItems)
    {
        //если есть подклассы
        if(!subClasses(class__).empty())
        {
            if ((subClasses(class__) + classesForInstance(instance)).size()
                    < subClasses(class__).size() + classesForInstance(instance).size())
            {
                return false;
            }
            classes_next += subClasses(class__);
        }
        else
        {
            hasEnd = true;
        }
    }
    if (hasEnd)
    {
        return true;
    }
    return isMinimalDown(instance, classes_next);
}

void Ontology::minimalize()
{

}


