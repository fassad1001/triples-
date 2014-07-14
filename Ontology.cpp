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
    QSet<QString> subclassInstances;

    subclases += className;
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
    properities += objectsFor(className, Ontology::HAS_PROPERTY);
    foreach(QString classToLoop, classesToLoop)
    {
        //(subject, predicate, object) (имяКласса;HAS_PROPERETY;*)
        properities += objectsFor(classToLoop, Ontology::HAS_PROPERTY);
    }
    return properities;
}

QSet<QString> Ontology::anyClassInstances(const QStringList &classNames) const
{
    //хранит все подклассы для аргументов классов
    QSet<QString> classNamess = classNames.toSet();
    //переменная хранит результаты работы метода (инстансы)
    QSet<QString> instanses;
    //на случай пустого значения аргумента
    if(classNames.isEmpty())
    {
        return QSet<QString>();
    }
    //для каждого аргумента
    foreach(const QString &className, classNames)
    {
        //дополняю классы подклассами
        classNamess += subClasses(className);
        //добавляю изначальный класс
        classNamess += className;
    }
    //для каждого класса
    foreach(const QString &className, classNamess)
    {
        //дополняю результат инстансами
        instanses += classInstances(className);
    }
    //возвращаю результат работы метода
    return instanses;
}

QSet<QString> Ontology::propertyValues(const QString &propertyName) const
{
    //переменная будет хранить результаты выполнения функции
    QSet<QString> propertyvalues;
    //получить список всех классов
    QSet<QString> allClassesItems = allClasses();
    //получить список-какбы-классов которые содержат свойство(;HAS_PROPERETY;имяСвойства)
    QSet<QString> testClasses = subjectsFor(Ontology::HAS_PROPERTY, propertyName);
    //если список-всех-классов содержит список-какбы-классов
    if(allClassesItems.contains(testClasses))
    {
        //для каждого класса
        foreach(const QString &classItem, testClasses)
        {
            //получить список всех инстансов которые относятся к этому классу (classInstances())
            QSet<QString> classinstances = classInstances(classItem);
            //для каждого полученного-интанса
            foreach(const QString &classinstance, classinstances)
            {
                //из списка взять значения для свойства (имяИнстанса;имяСвойства;) и записать их в результаты
                propertyvalues += objectsFor(classinstance, propertyName);
            }
        }
    }
    return propertyvalues;
}

MyHash Ontology::instanceProperties(const QString &instanceName) const
{
    //переменная будет хранить результат работы функции
    MyHash results;
    //для инстанса получить список классов к которым он относится
    QSet<QString> instanceClasses = classesForInstance(instanceName) & allClasses();
    //для каждого класса котый есть в иерархии
    foreach(const QString &instanceclass, instanceClasses)
    {
        //получить список свойств
        QSet<QString> instanceProperities = classProperties(instanceclass);
        //для каждого свойства
        foreach(const QString &instanceProperity, instanceProperities)
        {
            //получение значений в инстансе (instance;property;значение_которое_ищем)
            QSet<QString> values;
            values += objectsFor(instanceName,instanceProperity);
            if(values.isEmpty())
            {
                results.insert(instanceProperity, QString());
            }
            results.insert(instanceProperity, values.toList().first());
        }
    }

    //вернуть результат
    return results;
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
        const QSet<QString> allSubClases = subClasses(className);
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
    //переменная содержит результаты работы метода
    QSet<QString> classresults;
    //переменная содержит все классы
    const QSet<QString> allClassesItems = allClasses();
    //для каждого классса срежи всех классов
    foreach(const QString &classItem, allClassesItems)
    {
        //если класс содержит инстанс (входящий)
        if(classInstances(classItem).contains(instanceName))
        {
            //добавить его в первичные данные
            loopClasses += classItem;
        }
    }
    //записываю первоначальные данные для цикла
    classresults += loopClasses;
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
            classresults += exchangeClasses;
        }
        //передаю полученные данные для обработки в следуюющем цикле
        loopClasses = exchangeClasses;
    }
    //возвращаю результат работы программы
    return classresults;
}

QSet<QString> Ontology::instancesForProperties(const MyHash &values) const
{
    //переменная хранит результаты работы функции
    QSet<QString> results;
    //получить все классы allClasses()
    QSet<QString> allClassesItems = allClasses();
    //для каждого класса
    foreach(QString className, allClassesItems)
    {
        //получить все параметры (имя_класса,HAS_PROPERTY,) для класса
        QSet<QString> properties = objectsFor(className, Ontology::HAS_PROPERTY);
        //для каждого параметра
        foreach(QString property, properties)
        {
            //если вход содержит ключ имя_параметра
            if(values.contains(property))
            {
                //записать (,имя_параметра,значение_параметра) в результат
                foreach (QString value, values)
                {
                    results += subjectsFor(property, value);
                }
            }
        }
    }
    //вернуть результат
    return results;
}

QSet<QString> Ontology::instancesForNonProperties(const MyHash &values) const
{
    //переменная хранит результаты работы функции
    QSet<QString> results;
    //получить все классы allClasses()
    const QSet<QString> allClassesItems = allClasses();
    //получить все имена входящих параметров
    const QSet<QString> valuesProperties = values.keys().toSet();
    //для каждого класса
    foreach(QString className, allClassesItems)
    {
        //свойства, значения которых будут проверяться на несоответствие с входящими данными
        QSet<QString> propertiesToCheck = classProperties(className) & valuesProperties;
        //--проверка на несоответствие
        //для каждого параметра для проверки
        foreach(const QString &propertieToCheck, propertiesToCheck)
        {
            //если значения параметра-для-проверки не равно значению этого параметра их вход данных
            if(!propertyValues(propertieToCheck).contains(values.value(propertieToCheck)))
            {
                //добавить инстансы этого класса в результат
                results += classInstances(className);
            }
        }
    }
    //вернуть результат
    return results;
}

QSet<QString> Ontology::subClasses(const QString &className) const
{
    if(!allClasses().contains(className))
    {
        return QSet<QString>();
    }
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
            exchangeClasses += subjectsFor(Ontology::CONTAINS, loopclass);
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
    //переменная будет хранить в себе результат работы функции
    QSet<QString> result;
    //переменная будет хранить в себе результат пересечения классов
    QSet<QString> interSectionClasses;
    //записываю результат перечечения двух классов у инстансов
    interSectionClasses = objectsFor(instanceName1, Ontology::IS) & objectsFor(instanceName2, Ontology::IS);
    //переменная будет хранить в себе множество объектов типа Class для сортировки
    QList<Class> sortedClasses;
    //для каждого результата перечесения
    if(!interSectionClasses.isEmpty())
    {
        foreach(const QString &Name, interSectionClasses)
        {
            //запись результата в набор типа Class
            sortedClasses += Class(Name, superClasses(Name));
        }
    }
    //сортирую классы по принципу, если A содержит B то A<B
    qSort(sortedClasses.begin(), sortedClasses.end());
    //беру первый элемент как самый малый элемент и также беру
    if(!sortedClasses.isEmpty())
    {
        foreach(const Class &sortedClass, sortedClasses)
        {
            if(superClasses(sortedClass.name).count() == superClasses(sortedClasses.last().name).count())
            {
                result += sortedClass.name;
            }
        }
    }
    return result;
}

bool Ontology::isValid() const
{
    //переменная хранит в себе таблицу вида [Class1][Class2]=bool
    QHash<QString, QHash<QString, bool> > transitiveClosure;
    //переменная содержит в себе все классы
    QSet<QString> allClassesItems = allClasses();
    //переменная хранит в себе пары (класс;подкласс) выбираю по образцу (класс;CONTAINS;подкласс)
    QSet<Pair> closurePairs = subjectsAndObjects(Ontology::CONTAINS);
    //вариант 1
    //для каждого класса
    foreach(const QString &classItem1, allClassesItems)
    {
        //для каждого класса
        foreach(const QString &classItem2, allClassesItems)
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
        foreach(const QString &classItem1, allClassesItems)
        {
            //если (класс1, класс1, правда)
            if(transitiveClosure[classItem1][classItem1] == true)
            {
                //вернуть ложь;
                return false;
            }
            //для каждого класса
            foreach(const QString &classItem2, allClassesItems)
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
                foreach(const QString &classItem3, allClassesItems)
                {
                    if(classItem1 == classItem2)
                    {
                        continue;
                    }
                    //если (класс1, класс2, правда) && (класс2, класс3, правда) то
                    if(transitiveClosure[classItem1][classItem2] == true
                            && transitiveClosure[classItem2][classItem3] == true
                            && transitiveClosure[classItem1][classItem3] == false)
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

bool Ontology::isMinimal(QSet<Pair> &redundantPairs) const
{
    //переменная хранит все классы
    QSet<QString> allClassesItems = allClasses();
    //переменная хранит набор инстансов на подозрение
    QSet<QString> instances;
    //если иерархия валидна
    //для каждого класса
    foreach(const QString &class1, allClassesItems)
    {
        //для каждого класса
        foreach(const QString &class2, allClassesItems)
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
        //переменная будет хранить все классы для инcтанса в виде объектов "Class"
        QSet<Class> instanceClasses;
        //переменная хранит в себе классы для инстанса типа QString
        QSet<QString> classesForInstance = objectsFor(instance, Ontology::IS);
        //для каждого класса для инстанса (QString)
        foreach(const QString &instClass, classesForInstance)
        {
            //добавляю объект типа Class в набор классов для инстанса в виде объ типа Class
            QString className = instClass;
            QSet<QString> parents = superClasses(instClass);
            parents += instClass;
            instanceClasses += Class(className, parents);
        }
        //для каждого класса-для-инстанса
        foreach(const Class &instanceClass1, instanceClasses)
        {
            //для каждого класса-для-инстанса
            foreach(const Class &instanceClass2, instanceClasses)
            {
                if(instanceClass1.name == instanceClass2.name)
                {
                    continue;
                }
                //если класса-для-инстанса1 < класса-для-инстанса2
                if(instanceClass1 < instanceClass2)
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

void Ontology::minimalize()
{
    //переменная хранит все классы
    QSet<QString> allClassesItems = allClasses();
    //переменная хранит набор инстансов на подозрение
    QSet<QString> instances;
    //для каждого класса
    foreach(QString class1, allClassesItems)
    {
        //для каждого класса
        foreach(QString class2, allClassesItems)
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
        QSet<Class> instanceClasses;
        //переменная хранит в себе классы для инстанса типа QString
        QSet<QString> classesForInstanceItems = classesForInstance(instance);
        //для каждого класса для инстанса (QString)
        foreach(QString instClass, classesForInstanceItems)
        {
            //добавляю объект типа Class в набор классов для инстанса в виде объ типа Class
            instanceClasses += Class(instClass, superClasses(instClass));
        }
        //для каждого класса-для-инстанса
        foreach(Class instanceClass1, instanceClasses)
        {
            //для каждого класса-для-инстанса
            foreach(Class instanceClass2, instanceClasses)
            {
                //если класса-для-инстанса1 < класса-для-инстанса2
                if(instanceClass1 < instanceClass2)
                {
                    //удаляем связь (имяИнстанса;IS;класс-для-инатанса1)
                    //для устранения неминимальной связи
                    remove(instance, Ontology::IS, instanceClass1.name);
                }
            }
        }
    }
}

