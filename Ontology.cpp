#include "Ontology.h"

const QString Ontology::IS = "is";
const QString Ontology::CONTAINS = "contains";
const QString Ontology::CLASS = "class";


Ontology::Ontology()
{
}

Ontology::Ontology(const QSet<Triple> &triples) :
    TripleStorage(triples)
{
}

QSet<QString> Ontology::classInstances(const QString &className) const
{
    //переменная хранит в себе классы для цикла
    QSet<QString> classesForCicle;
    //переменная хранит в себе результаты
    QSet<QString> resultInstances;

    //добавляю первичные данные
    classesForCicle += className;
    //по первичным данным добавляю первые результаты (*, IS, имяКласса)
    resultInstances += subjectsFor(Ontology::IS, className);

    //пока есть классы для цикла
    while(!classesForCicle.empty())
    {
        //переменная будет хранить данные для следующей итерации
        QSet<QString> nextIteration;
        //для каждого класса-для-цикла
        foreach(const QString &classForCicle, classesForCicle)
        {
            //заполняем данные для следующей итерации
            nextIteration += subClasses(classForCicle);
        }
        //заполняем результат данными для след итерации
        resultInstances += nextIteration;
        //указываю данные для след итерации
        classesForCicle = nextIteration;
    }
    //возвращаем результат работы метода
    return resultInstances;
}

QSet<QString> Ontology::anyClassInstances(const QStringList &classNames) const
{
    //переменная хранит результаты работы метода (инстансы)
    QSet<QString> instanses;
    //для каждого класса
    foreach(const QString &className, classNames)
    {
        //дополняю результат инстансами
        instanses += classInstances(className);
    }
    //возвращаю результат работы метода
    return instanses;
}

QSet<QString> Ontology::allClassInstances(const QStringList &classNames) const
{
    //переменная хранит все классы в иерархии
    QSet<QString> allclasses = allClasses();
    //переменная хранит все инстансы-результаты-работы-метода
    QSet<QString> classinstances;
    //для каждого класса
    foreach(QString classItem, allclasses)
    {
        //дополняю результаты инстансами класса
        classinstances += classInstances(classItem);
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
    //возвращаю все что подходит по паттерну (имяИнстанса;IS;*)
    return objectsFor(instanceName, Ontology::IS);
}

QSet<QString> Ontology::subClasses(const QString &className) const
{
    //переменная будет хранить результаты (под классы)
    QSet<QString> subClasses;
    //переменная будет хранить классы для использования их в цикле
    QSet<QString> loopClasses;

    //записываю первоначальные данные для цикла
    loopClasses += className;
    //дополняю результаты с учетом первоначальных данных
    subClasses += objectsFor(className, Ontology::CONTAINS);
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
    //дополняю результаты с учетом первоначальных данных
    superClasses += subjectsFor(Ontology::CONTAINS, className);
    //пока есть данные для цикла
    while(!loopClasses.empty())
    {
        //переменная будет хранить классы для передачи их следующей итерации цикла
        QSet<QString> exchangeClasses;
        //для каждого класса (для цикла)
        foreach(QString loopclass, loopClasses)
        {
            //заполняю объекты для следующего цикла (*, CONSTAIN, имяКласса) это подклассы
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
    foreach(QString Name, interSectionClasses)
    {
        //запись результата в набор типа Class
        sortedClasses += Class(Name, superClasses(Name));
    }
    //сортирую классы по принципу, если A содержит B то A<B
    qSort(sortedClasses.begin(), sortedClasses.end());
    //беру первый элемент как самый малый элемент и возвращаю его
    return QSet<QString>()<<sortedClasses.at(0).name;
}

bool Ontology::isValid() const
{
    //переменная хранит в себе таблицу вида [Class1][Class2]=bool
    QHash<QString, QHash<QString, bool>> transitiveClosure;
    //переменная содержит в себе все классы
    QSet<QString> allclasses = allClasses();
    //переменная хранит в себе пары (класс;подкласс) выбираю по образцу (класс;CONTAINS;подкласс)
    QSet<Pair> closurePairs = subjectsAndObjects(Ontology::CONTAINS);
    //для каждой пары
    foreach(const Pair &closurePair, closurePairs)
    {
        //дополнить Хеш значением из пары
        transitiveClosure.insert(closurePair.first(), closurePair.second);
        //если есть замыкание на себе, то вернуть ложь
        //для каждого класса
        //если для (1,2) есть (2,3) то
        //создать связь (1,3)
    }
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
    //переменная хранит в себе метку (изменилось/не изменилось)
    bool change = false;
    //пока чтото изменяется
    do
    {
        //для каждого класса
        foreach(const QString &classItem1, allclasses)
        {
            //для каждого класса
            foreach(const QString &classItem2, allclasses)
            {
                //для каждого класса
                foreach(const QString &classItem1, allclasses)
                {
                    //если (класс1, класс2, правда) && (класс2, класс1, правда) то
                    if(transitiveClosure[classItem1][classItem2] == true
                            && transitiveClosure[closurePair.first()][closurePair.second()] == true)
                    {
                        //добавить (класс1, класс3, правда)
                        transitiveClosure[classItem1][classItem3] = true;
                        //установить метку (что-то изменилось)
                        change = true;
                    }
                }

            }
        }
    } while(change)




    QSet<QString> allclasses = allClasses();
    foreach(const QString classitem, allclasses)
    {
        classitem
    }

    QSet<QString> classes = allClasses();
    QSet<QString> loopclasses = allClasses();
    QSet<Pair> transitiveClosure

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
            QSet<QString> branch;
            branch += subClasses(classforinstance) += superClasses(classforinstance);
            foreach(const QString branchItem, branch)
            {
                //если класс ветви содержит сущность которую мы ищем
                if(classInstances(branchItem).contains(instance))
                {
                    //то сообщаем что вся иерархия не минимальна
                    return false;
                }
            }
        }
    }
    return true;
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
    QSet<QString> notMinimalInstances;
    foreach(QString instance, instances)
    {
        classesforinstance = classesForInstance(instance);
        //у нас могут быть как и те которые находятся на одной ветке так и те которые находятся на разных ветках
        //отсеиваем их по веткам
        //каждый класс - потенциально новая ветка
        foreach(const QString classforinstance, classesforinstance)
        {
            QSet<QString> branch;
            branch += subClasses(classforinstance) += superClasses(classforinstance);
            foreach(const QString branchItem, branch)
            {
                //если класс ветви содержит сущность которую мы ищем
                if(classInstances(branchItem).contains(instance))
                {
                    //то добавляем сущность в коллекцию на вывод
                    notMinimalInstances += instance;
                }
            }
        }
    }
    return notMinimalInstances;
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
            QList<QString> branch = subClasses(classforinstance).toList() + superClasses(classforinstance).toList();
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
            branchItemstoLoop.removeFirst();
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

bool Ontology::CompareByClassLvl(const QString &class1, const QString &class2)
{

}


