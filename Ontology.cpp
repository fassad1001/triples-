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
    qWarning()<<"classes"<<allClasses();
    foreach(const QString classf, allClasses())
    {
        qWarning()<<"))"<<objectsFor(Ontology::IS, classf);
        foreach(const QString instance, subjectsFor(Ontology::IS, classf))
        {
            qWarning()<<"+"<<instance;
            instances += instance;
        }
    }
    return instances;
}

QSet<QString> Ontology::classesForInstance(const QString &instanceName) const
{
    return objectsFor(instanceName, Ontology::IS);
}

QSet<QString> Ontology::classesForInstances(const QStringList &instanceNames) const
{
    QSet<QString> classes;
    //сбор всех возможных классов
    QSet<QString> musters;
    foreach(const QString instanceName, instanceNames)
    {
        musters += classesForInstance(instanceName);
    }
    bool is_uniq = true;
    //перебираем образцы на предмет их одновременности нахождения в искомом
    foreach(const QString muster, musters)
    {
        is_uniq = true;
        //по возможности помечаем элемент как неуникальный для двух элементов одновременно
        foreach(const QString instanceName, instanceNames)
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
    return objectsFor(className, Ontology::CONTAINS);
}

QSet<QString> Ontology::superClasses(const QString &className) const
{
    return subjectsFor(Ontology::CONTAINS, className);
}

QSet<QString> Ontology::mainSuperClass(const QString &instanceName1, const QString &instanceName2) const
{
    // ПОЛУЧИТЬ ВСЕ КЛАССЫ ДЛЯ instanceName1 И instanceName2, НАЙТИ ИХ ПЕРЕСЕЧЕНИЕ, В ПЕРЕСЕЧЕНИИ НАЙТИ МИНИМАЛЬНЫЕ КЛАССЫ ЧЕРЕЗ ФУНКЦИЮ qSort
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
    foreach(const QString class_, classes)
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
    foreach(const QString class_, classes)
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
    foreach (const QString class_, classes)
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
    foreach(const QString class_, classes)
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
    // ПОСТРОИТЬ ТРАНЗИТИВНОЕ ЗАМЫКАНИЕ, ОПРЕДЕЛИТЬ НАЛИЧИЕ ЦИКЛОВ В ГАФЕ

    QSet<QString> classes = allClasses();
    //ищу вершинки на выходе получаю список вершинок определенного уровня
    bool hasEnd;
    QSet<QString> levelItems;
    hasEnd = false;
    foreach(const QString class__, classes)
    {
        foreach(const QString class_, subClasses(class__))
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
    foreach(const QString checkClass, checkClasses)
    {
        //если есть подклассы
        if(subClasses(checkClass).size() != 0)
        {
            //для каждого подкласса делаю проверку
            foreach(const QString class_, subClasses(checkClass))
            {
                if (subClasses(class_).contains(checkClass))
                {
                    return false;
                }
            }
            classes_next += subClasses(checkClass);
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
    foreach(const QString instance, allinstances)
    {
        QSet<QString> instanceClasses = classesForInstance(instance);
        foreach(const QString instanceClass, instanceClasses)
        {
            if (!subClasses(instanceClass).empty())
            {
                foreach (const QString subclass, subClasses(instanceClass))
                {
                    if (classesForInstance(instance).contains(subclass))
                    {
                        return false;
                    }
                }
            }

            if (!superClasses(instanceClass).empty())
            {
                foreach(const QString superclass, superClasses(instanceClass))
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
    foreach(const QString class__, levelItems)
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
    foreach(const QString class__, levelItems)
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
    QSet<QString> instancesNotMin;
    QSet<QString> allinstances = allInstances();
    foreach(const QString instance, allinstances)
    {
        QSet<QString> instanceClasses = classesForInstance(instance);
        foreach(const QString instanceClass, instanceClasses)
        {
            if (!subClasses(instanceClass).empty())
            {
                if ((subClasses(instanceClass) + classesForInstance(instance)).size()
                        < subClasses(instanceClass).size() + classesForInstance(instance).size())
                {
                    instancesNotMin += instance;
                }
            }

            if (!superClasses(instanceClass).empty())
            {
                if ((superClasses(instanceClass) + classesForInstance(instance)).size()
                        < superClasses(instanceClass).size() + classesForInstance(instance).size())
                {
                    instancesNotMin += instance;
                }
            }
        }

        const bool minimalDown = isMinimalDown(instance, classesForInstance(instance));
        const bool minimalUp = isMinimalUp(instance, classesForInstance(instance));


        if (!minimalDown || !minimalUp)
        {
            instancesNotMin += instance;
        }
        //для каждого смотрим его класс и для этого класса смотрим все его подклассы для каждого подкласса
        //просматриваем наличие инстанса и если этот тот инстанс то возарвщаем ложь иначе возвращаем правду

        //для каждого смотри его класс и если у класса есть суперклассы то мы смотрим есть ли у суперкласса
        //просматриваем наличие инстанса и если этот тот инстанс то возарвщаем ложь иначе возвращаем правду
    }
    return instancesNotMin;
}

void Ontology::minimalize()
{
    QString minimalLvlClass;
    bool start = false;
    foreach(const QString notMinimalInstance, getNotMinimalInstances())
    {
        foreach(const QString className, classesForInstance(notMinimalInstance))
        {
            if(!start)
            {
                minimalLvlClass = className;
                start = true;
            }
            else
            {
                if (getClassLvl(className) < getClassLvl(minimalLvlClass))
                {
                    minimalLvlClass = className;
                }
            }
        }
        start = false;
        QSet<QString> classes = classesForInstance(notMinimalInstance) -= minimalLvlClass;
        qWarning()<<classes;
        qWarning()<<"before"<<classesForInstance(notMinimalInstance);
        foreach(const Triple tr, triples_)
        {
            qWarning()<<tr.toString();
        }
        foreach(const QString className, classes)
        {
            qWarning()<<"remove:"<<notMinimalInstance<<";"<<Ontology::IS<<";"<<className;
            triples_ -= Triple(notMinimalInstance, Ontology::IS, className);
        }
        qWarning()<<"after"<<classesForInstance(notMinimalInstance);
        qWarning()<<"result";
        foreach(const Triple tr, triples_)
        {
            qWarning()<<tr.toString();
        }
    }
}

bool Ontology::operator ==(const Ontology &o) const
{
    return triples_ == o.triples_;
}


