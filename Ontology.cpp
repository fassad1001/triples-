#include "Ontology.h"

const QString Ontology::IS = "is";
const QString Ontology::CONTAINS = "contains";
const QString Ontology::CLASS = "class";
const QString Ontology::HAS_PROPERTY = "has_properety";

Ontology::Ontology()
{
}

Ontology::Ontology(const QSet<Triple> &triples) :
    TripleStorage(triples)
{
}

QSet<QString> Ontology::classInstances(const QString &className) const
{
    QSet<QString> subclases = subClasses(className);
    subclases += className;
    QSet<QString> subclassInstances;
    foreach(const QString &subclass, subclases)
    {
        subclassInstances += subjectsFor(Ontology::IS, subclass);
    }
    return subclassInstances;
}

QSet<QString> Ontology::classProperties(const QString &className) const
{
    QSet<QString> classesToLoop;
    QSet<QString> properities;
    classesToLoop += className;
    classesToLoop += superClasses(className);
    foreach(QString classToLoop, classesToLoop)
    {
        //(subject, predicate, object) (имяКласса;HAS_PROPERETY;*)
        properities += objectsFor(classToLoop, Ontology::HAS_PROPERTY);
    }
}

QSet<QString> Ontology::anyClassInstances(const QStringList &classNames) const
{
    if(classNames.isEmpty())
    {
        return QSet<QString>()<<QString();
    }
    //переменная хранит результаты работы метода (инстансы)
    qWarning()<<"выполняю функцию anyClassInstances";
    qWarning()<<"++++++++++++++++++++++++++++++++++";
    qWarning()<<"на вход подаю имена классов :"<<classNames;
    qWarning()<<"начинаю выполнение функции...";
    QSet<QString> classNamess = classNames.toSet();
    foreach(const QString &className, classNames)
    {
        classNamess += subClasses(className);
    }
    QSet<QString> instanses;
    //для каждого класса
    foreach(const QString &className, classNamess)
    {
        //дополняю результат инстансами
        instanses += classInstances(className);
        qWarning()<<"+ "<<instanses;
    }
    //возвращаю результат работы метода
    qWarning()<<"выполнение функции закончилось";
    return instanses;
}

QSet<QString> Ontology::allClassInstances(const QStringList &classNames) const
{
    QSet<QString> classesToChoose;
    if(classNames.isEmpty())
    {
        return QSet<QString>();
    }
    QSet<QString> allSubClases = classNames.toSet();
    //извлекаю все подклассы у которых есть сущности
    foreach(const QString &className, classNames)
    {
        allSubClases += subClasses(className);
        foreach(const QString &subClassName, allSubClases)
        {
            if(!classInstances(subClassName).isEmpty())
            {
                classesToChoose += classInstances(subClassName);
            }
        }
    }
    //переменная хранит все инстансы-результаты-работы-метода
    QSet<QString> classinstances;
    classinstances += classesToChoose.toList().first();
    //для каждого класса
    foreach(QString classinstance, classinstances)
    {
        //дополняю результаты инстансами класса
        classinstances &= classInstances(classinstance);
    }
    //возвращаю инстанс-класса-результаты-работы-функции
    return classinstances;
}

QSet<QString> Ontology::allClasses() const
{
    //подбираю все что подходит (*, IS, CLASS)
    return subjectsFor(Ontology::IS, Ontology::CLASS);
}

QSet<QString> Ontology::allInstances() const
{
    //возвращает все инстансы в иерархии
    //переменная будет в себе хранить все найденые инстансы
    QSet<QString> instances;
    //переменная будет хранить в себе все классы
    QSet<QString> classes = allClasses();
    //для каждого класса
    foreach(const QString classItem, classes)
    {
        //ложу найденные инстансы в переменную
        instances += subjectsFor(Ontology::IS, classItem);
    }
    //возвращаю результат
    return instances;
}

QSet<QString> Ontology::classesForInstance(const QString &instanceName) const
{
    //переменная будет хранить классы для использования их в цикле
    QSet<QString> loopClasses;
    QSet<QString> classresults;
    qWarning()<<"выполняю функцию classesForInstance";
    qWarning()<<"+++++++++++++++++++++++++++++++++++++";
    qWarning()<<"на вход подаю :"<<instanceName;
    //записываю первоначальные данные для цикла
    loopClasses += objectsFor(instanceName, Ontology::IS);
    //пока есть данные для цикла
    while(!loopClasses.empty())
    {
        //переменная будет хранить классы для передачи их следующей итерации цикла
        QSet<QString> exchangeClasses;
        //для каждого класса (для цикла)
        foreach(QString loopclass, loopClasses)
        {
            //заполняю объекты для следующего цикла (*, CONSTAIN, имяКласса) это надклассы
            exchangeClasses += subjectsFor(Ontology::CONTAINS, loopclass);
            //дополняю результаты (+= инстансы для классов)
            qWarning()<<"+"<<exchangeClasses;
            classresults += classInstances(loopclass);
        }
        //передаю полученные данные для обработки в следуюющем цикле
        loopClasses = exchangeClasses;
    }
    //возвращаю результат работы программы
    qWarning()<<"выполнение функции закончилось";
    return classresults;
}

QSet<QString> Ontology::subClasses(const QString &className) const
{
    //переменная будет хранить результаты (под классы)
    QSet<QString> subClasses;
    //переменная будет хранить классы для использования их в цикле
    QSet<QString> loopClasses;

    //записываю первоначальные данные для цикла
    loopClasses += className;
    //пока есть данные для цикла
    while(!loopClasses.empty())
    {
        //переменная будет хранить классы для передачи их следующей итерации цикла
        QSet<QString> exchangeClasses;
        //для каждого класса (для цикла)
        foreach(QString loopclass, loopClasses)
        {
            //заполняю объекты для следующего цикла (имяКласса, CONSTAIN, *) это подклассы
            exchangeClasses += objectsFor(loopclass, Ontology::CONTAINS);
            //дополняю результаты
            subClasses += exchangeClasses;
        }
        //передаю полученные данные для обработки в следуюющем цикле
        loopClasses = exchangeClasses;
    }
    //возвращаю результат работы программы
    return subClasses;
}

QSet<QString> Ontology::superClasses(const QString &className) const
{
    //переменная будет хранить результаты (под классы)
    QSet<QString> superClasses;
    //переменная будет хранить классы для использования их в цикле
    QSet<QString> loopClasses;

    //записываю первоначальные данные для цикла
    loopClasses += className;
    //пока есть данные для цикла
    while(!loopClasses.empty())
    {
        //переменная будет хранить классы для передачи их следующей итерации цикла
        QSet<QString> exchangeClasses;
        //для каждого класса (для цикла)
        foreach(QString loopclass, loopClasses)
        {
            //заполняю объекты для следующего цикла (*, CONSTAIN, имяКласса) это суперклассы
            exchangeClasses += subjectsFor(Ontology::CONTAINS, className);
            //дополняю результаты
            superClasses += exchangeClasses;
        }
        //передаю полученные данные для обработки в следуюющем цикле
        loopClasses = exchangeClasses;
    }
    //возвращаю результат работы программы
    return superClasses;
}



QSet<QString> Ontology::mainSuperClass(const QString &instanceName1,
                                       const QString &instanceName2) const
{
    // ПОЛУЧИТЬ ВСЕ КЛАССЫ ДЛЯ instanceName1 И instanceName2, НАЙТИ ИХ ПЕРЕСЕЧЕНИЕ, В ПЕРЕСЕЧЕНИИ НАЙТИ МИНИМАЛЬНЫЕ КЛАССЫ ЧЕРЕЗ ФУНКЦИЮ qSort
    //переменная будет хранить в себе результат пересечения классов
    QSet<QString> interSectionClasses;
    //переменная будет хранить в себе отсортированный список
    QList<QString> sortedIntersectionClasses;
    //записываю результат перечечения двух классов у инстансов
    interSectionClasses = classesForInstance(instanceName1) & classesForInstance(instanceName2);
    //переменная будет хранить в себе множество объектов типа Class для сортировки
    QList<Class> sortedClasses;
    //для каждого результата перечесения
    if(!interSectionClasses.isEmpty())
    {
        foreach(QString Name, interSectionClasses)
        {
            //запись результата в набор типа Class
            sortedClasses += Class(Name, superClasses(Name));
        }
    }
    //сортирую классы по принципу, если A содержит B то A<B
    qSort(sortedClasses.begin(), sortedClasses.end());
    //беру первый элемент как самый малый элемент и возвращаю его
    if(!sortedClasses.isEmpty())
    {
        return QSet<QString>()<<sortedClasses.at(0).name;
    }
    return QSet<QString>();
}

bool Ontology::isValid() const
{
    //переменная хранит в себе таблицу вида [Class1][Class2]=bool
    QHash<QString, QHash<QString, bool> > transitiveClosure;
    //переменная содержит в себе все классы
    QSet<QString> allclasses = allClasses();
    //переменная хранит в себе пары (класс;подкласс) выбираю по образцу (класс;CONTAINS;подкласс)
    QSet<Pair> closurePairs = subjectsAndObjects(Ontology::CONTAINS);
    //вариант 1
    //для каждого класса
    foreach(const QString &classItem1, allclasses)
    {
        //для каждого класса
        foreach(const QString &classItem2, allclasses)
        {
            //добавить в таблицу (класс1, класс2, ложь)
            transitiveClosure[classItem1][classItem2] = false;
        }
    }

    //для каждой пары
    foreach(const Pair &closurePair, closurePairs)
    {
        //добавить в таблицу (класс1, класс2, правда)
        transitiveClosure[closurePair.first()][closurePair.second()] = true;
    }
    bool changed;
    do
    {
        changed = false;
        //для каждого класса
        foreach(const QString &classItem1, allclasses)
        {
            //если (класс1, класс1, правда)
            if(transitiveClosure[classItem1][classItem1] == true)
            {
                //вернуть ложь;
                return false;
            }
            //для каждого класса
            foreach(const QString &classItem2, allclasses)
            {
                //если (класс2, класс2, правда)
                if(transitiveClosure[classItem2][classItem2] == true)
                {
                    //вернуть ложь;
                    return false;
                }
                //если (класс1, класс2, правда) && (класс2, класс1, правда)
                if(transitiveClosure[classItem1][classItem2] == true
                        && transitiveClosure[classItem2][classItem1] == true)
                {
                    //вернуть ложь;
                    return false;
                }
                //для каждого класса
                foreach(const QString &classItem3, allclasses)
                {
                    if(classItem1 == classItem2)
                    {
                        continue;
                    }
                    //если (класс1, класс2, правда) && (класс2, класс3, правда) то
                    if(transitiveClosure[classItem1][classItem2] == true
                            && transitiveClosure[classItem2][classItem3] == true
                            || transitiveClosure[classItem1][classItem3])
                    {
                        //добавить (класс1, класс3, правда)
                        transitiveClosure[classItem1][classItem3] = true;
                        //установить метку (что-то изменилось)
                        changed = true;
                        // **проверка на наличие циклов
                        //если (класс1, класс3, правда) && (класс3, класс1, правда) то
                        if((transitiveClosure[classItem1][classItem3] == true
                            && transitiveClosure[classItem3][classItem1] == true)
                                || (transitiveClosure[classItem3][classItem3] == true))
                        {
                            //вернуть ложь;
                            return false;
                        }
                    }
                }

            }
        }

    }while(changed);
    return true;
}

bool Ontology::isMinimal() const
{
    //переменная хранит все классы
    QSet<QString> allclasses = allClasses();
    //переменная хранит набор объектов типа "Класс"
    QSet<Class> classes;
    //переменная хранит набор инстансов на подозрение
    QSet<QString> instances;
    //если иерархия валидна
    if(isValid())
    {
        //для каждого класса
        foreach(const QString &class1, allclasses)
        {
            //для каждого класса
            foreach(const QString &class2, allclasses)
            {
                //если слассы одни и теже
                if(class1 == class2)
                {
                    continue;
                }
                //если пересечение инстансов-класса дает положительный результат
                if(!(classInstances(class1) & classInstances(class2)).isEmpty())
                {
                    //записываем результат в список инстансов на подозрение
                    instances += classInstances(class1) & classInstances(class2);
                }
            }
        }
        //для каждого элемента-списка-на-подозрение
        foreach(const QString &instance, instances)
        {
            //переменная будет хранить все классы для интанса в виде объектов "Class"
            QSet<Class> instanceclasses;
            //переменная хранит в себе классы для инстанса типа QString
            QSet<QString> classesforinstance = classesForInstance(instance);
            //для каждого класса для инстанса (QString)
            foreach(const QString &instClass, classesforinstance)
            {
                //добавляю объект типа Class в набор классов для инстанса в виде объ типа Class
                QString className = instClass;
                QSet<QString> parents = superClasses(instClass);
                instanceclasses += Class(className, parents);
            }
            //для каждого класса-для-инстанса
            foreach(const Class &instanceclass1, instanceclasses)
            {
                //для каждого класса-для-инстанса
                foreach(const Class &instanceclass2, instanceclasses)
                {
                    if(instanceclass1.name == instanceclass2.name)
                    {
                        continue;
                    }
                    //если класса-для-инстанса1 < класса-для-инстанса2
                    if(instanceclass1 < instanceclass2)
                    {
                        //вернуть ложь
                        return false;
                    }
                }
            }
        }
        //вернуть правду
        return true;
    }
    //вернуть ложь
    return false;
}

void Ontology::minimalize()
{
    //переменная хранит все классы
    QSet<QString> allclasses = allClasses();
    //переменная хранит набор объектов типа "Класс"
    QSet<Class> classes;
    //переменная хранит набор инстансов на подозрение
    QSet<QString> instances;
    //для каждого класса
    foreach(QString class1, allclasses)
    {
        //для каждого класса
        foreach(QString class2, allclasses)
        {
            //если пересечение инстансов-класса дает положительный результат
            if(!(classInstances(class1) & classInstances(class2)).isEmpty() && class1 != class2)
            {
                //записываем результат в список инстансов на подозрение
                instances += classInstances(class1) & classInstances(class2);
            }
        }
    }
    //для каждого элемента-списка-на-подозрение
    foreach(QString instance, instances)
    {
        //переменная будет хранить все классы для интанса в виде объектов "Class"
        QSet<Class> instanceclasses;
        //переменная хранит в себе классы для инстанса типа QString
        QSet<QString> classesforinstance = classesForInstance(instance);
        //для каждого класса для инстанса (QString)
        foreach(QString instClass, classesforinstance)
        {
            //добавляю объект типа Class в набор классов для инстанса в виде объ типа Class
            instanceclasses += Class(instClass, superClasses(instClass));
        }
        //для каждого класса-для-инстанса
        foreach(Class instanceclass1, instanceclasses)
        {
            //для каждого класса-для-инстанса
            foreach(Class instanceclass2, instanceclasses)
            {
                //если класса-для-инстанса1 < класса-для-инстанса2
                if(instanceclass1 < instanceclass2)
                {
                    //удаляем связь (имяИнстанса;IS;класс-для-инатанса1)
                    //для устранения неминимальной связи
                    triples_ -= Triple(instance, Ontology::IS, instanceclass1.name);
                }
            }
        }
    }
}

bool Ontology::operator ==(const Ontology &o) const
{
    return triples_ == o.triples_;
}

